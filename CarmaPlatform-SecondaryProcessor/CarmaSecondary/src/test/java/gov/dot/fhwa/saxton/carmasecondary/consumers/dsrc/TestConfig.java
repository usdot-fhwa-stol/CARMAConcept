package gov.dot.fhwa.saxton.carmasecondary.consumers.dsrc;

import gov.dot.fhwa.saxton.carmasecondary.utils.AppConfig;
import gov.dot.fhwa.saxton.carmasecondary.utils.IAppConfig;

import java.util.Properties;

/**
 * Created by starkj on 2/19/2016.
 */
class TestConfig extends AppConfig implements IAppConfig {
    /**
     * Intended for use in testing - test setup method can define all the properties here and
     * avoid loading a particular file.
     */
    public void setProperty(String name, String value) {
        if (properties == null) {
            properties = new Properties();
        }

        properties.setProperty(name, value);
    }

    public static IAppConfig getInstance() { return _instance; }

    private static final  TestConfig _instance = new TestConfig();
}

