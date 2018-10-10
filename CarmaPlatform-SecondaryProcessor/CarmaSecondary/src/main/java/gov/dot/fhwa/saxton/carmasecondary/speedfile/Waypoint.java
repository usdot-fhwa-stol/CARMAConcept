package gov.dot.fhwa.saxton.carmasecondary.speedfile;

/**
 * Waypoint
 * 
 * Defines a waypoint in the speed profile.
 *
 * @author Fang
 */
public class Waypoint {

	private String	id;
	private double	lat;
	private double	lon;
	private double	speed;
	private double	accel;
	private double	radius;
	private int		headway;
	private boolean singleUse;
	private boolean	available;
	
	public Waypoint(String id, double lat, double lon, double speed, double accel, double radius,
					int headway, boolean singleUse){

		this.id = id;
		this.lat = lat;
		this.lon = lon;
		this.speed = speed;
		this.accel = accel;
		this.radius = radius;
		this.headway = headway;
		this.singleUse = singleUse;
		this.available = true;
	}

	public String getId() {return id; }
	
	public double getLat(){
		return lat;
	}
	
	public double getLon(){
		return lon;
	}
	
	public double getSpeed(){
		return speed;
	}
	
	public double getAccel(){
		return accel;
	}
	
	public double getRadius(){
		return radius;
	}

	public int getHeadway(){
		return headway;
	}

	public boolean isAvailable() { return available; }

	public boolean isSingleUse() { return singleUse; }

	/**
	 * Indicates that this waypoint has been used. If it is a single-use waypoint
	 * then it will no longer be available for future use.
	 */
	public void markUsed() {
		available = !singleUse;
	}

}