package gov.dot.fhwa.saxton.carmasecondary.speedfile;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.util.List;

import gov.dot.fhwa.saxton.carmasecondary.logger.ILogger;
import gov.dot.fhwa.saxton.carmasecondary.logger.LoggerManager;
import gov.dot.fhwa.saxton.carmasecondary.utils.AppConfig;
import gov.dot.fhwa.saxton.carmasecondary.utils.IAppConfig;

/**
 * SpeedCmdProcessor
 * 
 * Get vehicle current gps coordinate and check distances to waypoints.
 * Send corresponding speed command to MAB on mab.spdcmd.port.
 *
 * Uses config properites:
 * 		mab.host
 * 		mab.spdcmd.port
 * 		speedFile.enable
 * 		speedFile.path
 * 		singleuse.waypoints.enable
 * 		speed.initial
 * 		accel.initial
 * 		headway.initial
 * 
 * @author Fang
 * 
 */
public class SpeedCmdProcessor{
	
	private static ILogger logger = LoggerManager.getLogger(SpeedCmdProcessor.class);
	
	// MAB configuration for sending speed and accel commands from Linux PC to MAB	
    private String				mabIp;
    private int					mabUdpPort;
    private InetSocketAddress	mabAddress;
    private DatagramSocket		mabSocket;

	protected boolean			profileDesired;	//is a speed profile to be used?
	protected String			speedFileName;	//holds the speed profile data
	protected boolean			globalSingleUse;//does the user want to mark individual WPs as single-use?
	protected double 			speedCmd;		//the speed command currently in use, mph
	protected double 			maxAccel;		//the max accel currently in use, m/s2
	protected int 				headway;		//the headway currently in use, ms
	protected List<Waypoint>	waypoints;
	protected SpeedFileMgr		speedFileMgr;

	//waypoint processing
	protected boolean			crossingWp;		//are we currently crossing a waypoint?
	protected int				curWpIndex;		//index in the waypoints array of the one we are crossing
	protected double			curWpDistance;	//closest proximity distance to the waypoint, m

    /**
     * Constructor
     */
    public SpeedCmdProcessor(IAppConfig config)   {
		speedFileMgr = new SpeedFileMgr(config);
		this.mabUdpPort = config.getIntValue("mab.spdcmd.port");
        this.mabIp = config.getProperty("mab.host");
        this.mabAddress = new InetSocketAddress(mabIp, mabUdpPort);
		this.profileDesired = false;
		this.globalSingleUse = false;
		try {
			String prop = config.getProperty("speedFile.enable");
			this.profileDesired = prop.equals("true");
			prop = config.getProperty("singleuse.waypoints.enable");
			this.globalSingleUse = prop.equals("true");
		}catch (Exception e) {
			//continue since we set default value above
		}
		if (profileDesired) {
			speedFileName = config.getProperty("speedFile.path");
		}

		//initialize the commands going to the MAB, preferably from the config file
		speedCmd = 35; //mph
		maxAccel = 1; //m/s2
		headway = 65000; //ms
		try {
			speedCmd = config.getDoubleValue("speed.initial");
			maxAccel = (float)config.getDoubleValue("accel.initial");
			headway = config.getIntValue("headway.initial");
			
		}catch (Exception e) {
			//continue since we have reasonable values above
		}
		

		//we start outside of all waypoints
		crossingWp = false;
		curWpIndex = -1;
		curWpDistance = 999999.0;
    }

	/**
	 * Reads speed profile and sets up a UDP connection to the MAB for passing speed commands.
	 */
    public void initialize() throws Exception {
    	Boolean socketOpen = false;

		//read the speed profile file if desired
		if (profileDesired) {
			try {
				waypoints = speedFileMgr.parseCSV(speedFileName);

			}catch (Exception e) {
				logger.error("SPD-FL", "Error reading speed profile (" + speedFileName + "): " + e.getMessage());
				throw e;
			}
		}

		//set up the communications socket with the MAB
    	try{
    		mabSocket = new DatagramSocket(mabUdpPort);
    		socketOpen = true;
        	logger.info("SPD-FL", "Established MAB socket for SpeedCmdProcessor on port: " + mabUdpPort);
    	}catch(Exception e)   {
    		logger.error("SPD-FL", "Error starting SpeedCmdProcessor socket. " + e.getMessage());
			throw e;
    	}  	
    }
    
	/**
	 * Generate a speed command based on the vehicle's location relative to any waypoints defined.
	 * This method is a state machine. If it is "crossing a waypoint" (i.e. within that waypoint's
	 * proximity circle and has already identified this waypoint as the next available one that
	 * applies to current vehicle position), then it will use that waypoint's commands and ignore
	 * all other waypoints.  Once it leaves that particular proximity circle, it is considered
	 * "between waypoints", and will start searching for a new waypoint. This search starts at the
	 * top of the list and identifies the first one whose proximity circle encompases the current
	 * vehicle location, and that is still marked as available (single-use waypoints may no longer
	 * be available).
	 *
	 * @param myLat
	 * @param myLon
     */
    public void generateSpeedCmd(double myLat, double myLon){    	
		//if we are crossing a waypoint then
		if (crossingWp) {
			//if we are no longer inside its proximity circle then
			Waypoint wp = waypoints.get(curWpIndex);
			double distance = calDistance(myLat, myLon, wp.getLat(), wp.getLon());
			if (distance <= wp.getRadius()) {
				if (distance < curWpDistance) {
					curWpDistance = distance;
				}
			}else {
				//indicate that we are now between waypoints
				logger.infof("SPD-FL", "Exiting waypoint %s proximity. Nearest approach was %.1f m", wp.getId(), curWpDistance);
				crossingWp = false;
				curWpIndex = -1;
				curWpDistance = 999999.0;
			}

		//else (between waypoints)
		}else {
			//look for a new waypoint that we might be entering
			curWpIndex = findNewWp(myLat, myLon);

			//if one was found then
			if (curWpIndex >= 0) {
				//indicate that we are now crossing a waypoint and store its index
				crossingWp = true;
			}
		}

		sendSpdCmdtoMAB(speedCmd, maxAccel, headway);
    }

	/**
	 * Searches for a waypoint that vehicle might be close enough to to begin crossing.
	 * @param myLat
	 * @param myLon
	 * @return index into waypoints array of the newly found waypoint, or -1 if nothing found
	 * Also sets the member command variables speedCmd, maxAccel, headway.
     */
	protected int findNewWp(double myLat, double myLon) {
		int foundIndex = -1;

		if (waypoints != null) { //waypoints will be null if the global flag is off
            for (int i = 0;  i < waypoints.size();  ++i) {
				Waypoint wp = waypoints.get(i);

                //if this waypoint is still in use then
                if (wp.isAvailable()) {

                    double csvLat = wp.getLat();
                    double csvLon = wp.getLon();
                    double csvSpeedCmd = wp.getSpeed();
                    double csvMaxAccel = wp.getAccel();
                    double csvRadius = wp.getRadius();
                    int csvHeadway = wp.getHeadway();
                    double distance = calDistance(myLat, myLon, csvLat, csvLon);                 

                    //if the vehicle is within the radius of this waypoint then
                    if (distance <= csvRadius){
						curWpDistance = distance;
                        //use the commands from this waypoint
						foundIndex = i;
                        speedCmd = csvSpeedCmd;
                        maxAccel = csvMaxAccel;
                        headway = csvHeadway;
                         
                        //if the single-use waypoint capability is turned on then we need to mark this waypoint as used
                        if (globalSingleUse) {
                            wp.markUsed();		//this may make it unavailable for future use
                        }

                        //when find the first waypoint within this waypoint's radius, exit For loop
                        logger.infof("SPD-FL", "-----Entering waypoint: %s (dist=%.2f), spd=%.2f acc=%.1f gap=%d",
                                wp.getId(), distance, csvSpeedCmd, csvMaxAccel, csvHeadway);
                        break;
                    }
                }
            }
        }

		return foundIndex;
	}

	/**
	 * Calculate the distance between two GPS points using Haversine formula
	 * @param lat1, decimal degrees
	 * @param lon1, decimal degrees
	 * @param lat2, decimal degrees
	 * @param lon2, decimal degrees
	 * @return
	 */
	protected double calDistance(double lat1, double lon1, double lat2, double lon2){

		double R = 6372800.0;	//meters
		double dLat = Math.toRadians(lat2 - lat1);
		double dLon = Math.toRadians(lon2 - lon1);
		lat1 = Math.toRadians(lat1);
		lat2 = Math.toRadians(lat2);

		double a = Math.pow(Math.sin(dLat / 2), 2) + Math.pow(Math.sin(dLon / 2), 2) * Math.cos(lat1) * Math.cos(lat2);
		double c = 2 * Math.asin(Math.sqrt(a));
		return R * c;
	}

	protected void sendSpdCmdtoMAB(double speedCmd, double accelCmd, int headwayCmd) {
		byte[] speedCmdMessage = new byte[6];

		//amplify float speedCmd, float scale: 0.01
		int intSpeedCmd = (int)(speedCmd/0.01);
		//amplify float accel, float scale: 0.01
		int intAccelCmd = (int)(accelCmd/0.01);

		//build the command message
		// 6 Bytes speed, acceleration and gap timing/headway command message
		// byte[0] is message header: 0xff
		// speedCmd (mph): byte[1] and byte[2]
		// accelCmd(cm/s/s): byte[3]
		// headwayCmd(ms): byte[4] and byte[5]
		// to avoid errors when different systems parse the byte array to float
		speedCmdMessage[0] = (byte)0xff;
		speedCmdMessage[2] = (byte)(intSpeedCmd >> 8);
		speedCmdMessage[1] = (byte)(intSpeedCmd);
		speedCmdMessage[3] = (byte)intAccelCmd;
		speedCmdMessage[4] = (byte)(headwayCmd >> 8);
		speedCmdMessage[5] = (byte)(headwayCmd);

		// Send speed, accel and headway commands to MAB
		try{
		    		    
         	DatagramPacket sendPacket = new DatagramPacket(speedCmdMessage, speedCmdMessage.length, mabAddress);
         	mabSocket.send(sendPacket);
         	logger.info("SPD-FL", "Speed, Acceleration and Headway Commands sent to MAB " + speedCmdMessage.length + " bytes on to: " + mabIp + ":" + mabUdpPort);
		}catch (SocketException e) {
            logger.warn("SPD-FL", "read: socket exception, " + e.getMessage());
        } catch (IOException e) {
            logger.warn("SPD-FL", "read: IO exception, " + e.getMessage());
        }
		logger.debug("SPD-FL", "Speed and Acceleration Commands: " + javax.xml.bind.DatatypeConverter.printHexBinary(speedCmdMessage));
	}
	
	private void closeConnection() {
		logger.info("SPD-FL", "Stopping MAB Speed Command thread for port: " + mabUdpPort);
		try {
			mabSocket.close();
		} catch (Exception e) {
			logger.error("SPD-FL", "Error closing MAB Speed Command for ports: " + mabUdpPort + ", " + e.getMessage());
		}		
	}
}
