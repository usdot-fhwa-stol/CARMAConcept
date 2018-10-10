package gov.dot.fhwa.saxton.carmasecondary.utils;

/**
 * This interface intentionally does not specify any methods for populating the config properties; that is left up
 * to the implementing class.
 */
public interface IAppConfig {

    /**
     * Returns the property value corresponding to the provided property name, typically stored as key-value pairs.
     * @param name - the name of the property desired (e.g. the key)
     * @return the value of the named property, or null if not found
     */
    public String getProperty(String name);

    public boolean getBooleanValue(String name);

    public int getIntValue(String name);

    public int getDefaultIntValue(String name, int defaultValue);

    public double getDoubleValue(String name);

    public double getDefaultDoubleValue(String name, double defaultValue);
}
