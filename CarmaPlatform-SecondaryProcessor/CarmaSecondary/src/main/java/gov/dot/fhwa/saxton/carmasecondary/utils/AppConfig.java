package gov.dot.fhwa.saxton.carmasecondary.utils;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * This singleton class provides access to configuration properties stored in any specified file
 */
public class AppConfig implements IAppConfig {

    // This is not a true singleton, as the default constructor is public. It is public to allow subclassing,
    // which will facilitate simpler unit testing (e.g. adding methods to set property values without reading
    // them from a file), and also allows addition of custom property retrieval methods that add more
    // sophistication for application-specific use.  Since this is an eager initialization (the instance_ is
    // created after class load) of a static instance variable, there is no chance of having multiple instances
    // even if there are multiple object copies in use.

    private static class AppConfigHolder {
        private static final AppConfig instance_ = new AppConfig();
    }

    public static IAppConfig getInstance() { return AppConfigHolder.instance_; }

    public AppConfig() { }



    ///// working methods

    /**
     * Initializes the properties from a file of key-value pairs
     * @param propertiesFile - full path to the file
     */
    public void loadFile(String propertiesFile) throws Exception {

        InputStream in = null;

        //look for the properties file in the current working directory
        try {
            String fullPath = "./" + propertiesFile;
            in = new FileInputStream(fullPath);
        } catch (IOException e1) {

            //if not found then look for it in the classpath
            in = getClass().getClassLoader().getResourceAsStream(propertiesFile);
        }

        //if file has been found then read it and load up the properties object
        try {
            if (in != null) {
                properties.load(in);
            } else {
                throw new FileNotFoundException("File " + propertiesFile + " not found in current directory or classpath.");
            }

        } catch (Exception e3) {
            throw e3;
        } finally {
            in.close();
        }
    }

    public String getProperty(String name) {
        return properties.getProperty(name);
    }

    public boolean getBooleanValue(String property)   {
        boolean bValue = false;

        String value = getProperty(property);
        if (value == null || value.isEmpty())  {
            bValue = false;
        }
        else   {
            bValue = Boolean.parseBoolean(value);
        }

        return bValue;
    }

    public int getIntValue(String property)   {
        String value = properties.getProperty(property);
        return Integer.parseInt(value);
    }

    /**
     * Returns provided default value if property is not in properties file
     *
     * @param property
     * @param defaultValue
     * @return int
     */
    public int getDefaultIntValue(String property, int defaultValue)   {
        String value = properties.getProperty(property);
        if (value == null)   {
            return defaultValue;
        }

        int result = defaultValue;
        try   {
            result = Integer.parseInt(value);
        }
        catch(Exception e) {
            //ignore it
        }

        return result;
    }

    public double getDoubleValue(String name) {
        String value = properties.getProperty(name);
        double v = Double.parseDouble(value);
        return v;
    }

    public double getDefaultDoubleValue(String name, double defaultValue) {
        String value = properties.getProperty(name);
        if (value == null) {
            return defaultValue;
        }

        double result = defaultValue;
        try {
            result = Double.parseDouble(value);
        }
        catch (Exception e) {
            //ignore it
        }
        return result;
    }

    @Override
    public String toString() {
        if (properties != null) {
            return properties.toString();
        }else {
            return "FILE NOT YET LOADED";
        }
    }

    /////////////////////
    // protected elements
    /////////////////////

    protected Properties            properties = new Properties();

}