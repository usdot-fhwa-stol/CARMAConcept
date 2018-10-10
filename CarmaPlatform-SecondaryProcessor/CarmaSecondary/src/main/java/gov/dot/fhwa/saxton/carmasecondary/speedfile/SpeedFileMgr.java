package gov.dot.fhwa.saxton.carmasecondary.speedfile;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import gov.dot.fhwa.saxton.carmasecondary.utils.IAppConfig;
import gov.dot.fhwa.saxton.carmasecondary.logger.ILogger;
import gov.dot.fhwa.saxton.carmasecondary.logger.LoggerManager;

import org.apache.commons.csv.CSVFormat;
import org.apache.commons.csv.CSVParser;
import org.apache.commons.csv.CSVRecord;

/**
 * SpeedFileMgr
 * 
 * Parse the speed profile
 * Calculate distance between two gps coordinates
 * Assemble speed & accel commands
 * 
 * Uses config properties:
 * 		None
 *
 * @author Fang
 */
public class SpeedFileMgr {
	
	private static ILogger logger = LoggerManager.getLogger(SpeedFileMgr.class);
	
	private List<Waypoint> speedFileDataList;
	
	public SpeedFileMgr(IAppConfig config){
		//does not use config file properties at this time.
	}
	

	/**
	 * Read the CSV file to get rows with the following data elements:
     *     Waypoint ID (any non-empty string)
     *     Latitude(decimal degrees)
     *     Longitude(decimal degrees)
     *     Speed command(mph)
	 *     Acceleration(m/s/s)
     *     Radius(meter)
     *     Headway(ms)
     *     Single-use flag (S or s = use one time only, anything else = persistent (default); optional)
	 * Parse the rows into List<Waypoint>.  Will skip over blank lines and comments beginning with #
     *
	 * @throws Exception 
	 */
	public List<Waypoint> parseCSV(String speedFilePath)throws Exception{

		String	csvId;
		double	csvLat;
		double	csvLon;
		double	csvSpeed;
		double	csvAccel;
		double	csvRadius;
		int		csvHeadway;
		boolean	csvSingleUse;
		CSVParser parser = null;

		try{
			//create a new array to hold the waypoint data (in case this method is called multiple times)
			speedFileDataList = new ArrayList<Waypoint>();
			logger.info("SPD-FL", "Starting to read the speed profile: " + speedFilePath);

			//configre a formatter to allow comments and blank lines in the file
			CSVFormat format = CSVFormat.EXCEL.withCommentMarker('#').withIgnoreEmptyLines(true);

			// creates a CSV parser with the CSV file format
		    parser = new CSVParser(new FileReader(speedFilePath), format);

		    //check the value of data in each record, e.g., speed >= 0
		    //if all data are valid, add into the list of waypoints.
			if (parser != null) {
				for (CSVRecord r : parser) {

					csvId = r.get(0);
					csvLat = Double.parseDouble(r.get(1));
					csvLon = Double.parseDouble(r.get(2));
					csvSpeed = Float.parseFloat(r.get(3));
					csvSpeed = (int) (csvSpeed*100 + 0.5);
					csvSpeed = csvSpeed/100;
					csvAccel = Float.parseFloat(r.get(4));
					csvRadius = Double.parseDouble(r.get(5));
					csvHeadway = (int) (Double.parseDouble(r.get(6)) + 0.5);
					csvSingleUse = false;
					if (r.size() > 7) { //the single-use flag is optional
						csvSingleUse = r.get(7).trim().equalsIgnoreCase("S");
					}

					//id cannot be null
					if (csvId.length() == 0) {
						logger.warn("SPD-FL", "Invalid waypoint data - ID is null");
						throw new IllegalArgumentException("Error: invalid data input (ID is null)");
					}

					//geo-fencing rectangle area to restrict the input of lat and long
					//the area includes Aberdeen, MD and also part of VA, Washington D.C. and MD
					if (csvLat < 38.273046 || csvLat > 39.713971) {
						logger.warn("SPD-FL", "Invalid waypoint data - latitutde out of bounds for ID " + csvId);
						throw new IllegalArgumentException("Error: Invalid data input (Latitude " + csvLat + ")");
					}
					if (csvLon < -78.213756 || csvLon > -75.794309) {
						logger.warn("SPD-FL", "Invalid waypoint data - longitude out of bounds for ID " + csvId);
						throw new IllegalArgumentException("Error: Invalid data input (Longitude " + csvLon + ")");
					}

					//speed must be positive, can be 0
					if (csvSpeed < 0) {
						logger.warn("SPD-FL", "Invalid waypoint data - speed command illegal for ID " + csvId);
						throw new IllegalArgumentException("Error: Invalid data input (Speed" + csvSpeed + ")");
					}

					//acceleration must be positive
					//the maximum acceleration that TORC system can handle is 2.5 m/s2
					if (csvAccel <= 0 || csvAccel > 2.5) {
						logger.warn("SPD-FL", "Invalid waypoint data - acceleration out of bounds for ID " + csvId);
						throw new IllegalArgumentException("Error: Invalid data input (Accelaration " + csvAccel + ")");
					}

					//radius must be positive
					if (csvRadius <= 0) {
						logger.warn("SPD-FL", "Invalid waypoint data - radius out of bounds for ID " + csvId);
						throw new IllegalArgumentException("Error: Invalid data input (Radius " + csvRadius + ")");
					}

					//Set minimum headway to 500 ms, agreed by John Stark.
					//When the value of the headway is 65000 ms, use factory settings.
					//Max radar distance is 75 meters, meaning speed*headway <= 75 meters
					//The unit of csvSpeed is mph and the unit of headway is ms
					//Convert csvSpeed to m/s: csvSpeed*0.44704
					//Therefore, csvSpeed*0.44704*csvHeadway/1000 <= 75 meters,
					//which could represent as csvSpeed*csvHeadway <= 167770
					if (csvHeadway < 500 || (csvSpeed * csvHeadway > 167770 && csvHeadway != 65000)) {
						logger.warn("SPD-FL", "Invalid waypoint data - headway out of bounds for ID " + csvId);
						throw new IllegalArgumentException("Error: Invalid data input (Gap Timing: " + csvHeadway + ")");
					}

					//if we have gotten to here, then the record is all valid, so create the waypoint object
					speedFileDataList.add(
							new Waypoint(csvId, csvLat, csvLon, csvSpeed, csvAccel, csvRadius, csvHeadway, csvSingleUse));
				}
			}
		    logger.info("SPD-FL", speedFilePath + " is sucessfully loaded with " + speedFileDataList.size() + " waypoints.");

		} catch (FileNotFoundException e) {
			logger.error("SPD-FL", "read: FileNotFound exception message: " + e.toString());
			throw e;
		} catch (IOException ioe) {
			logger.error("SPD-FL", "read: IO exception: " + ioe.toString());
			throw ioe;
		} catch (Exception ee) {
			logger.error("SPD-FL", "rea: Exception: " + ee.toString());
			throw ee;
		}finally {
			if (parser != null) {
				parser.close();
			}
		}

		return speedFileDataList;
	}
}

