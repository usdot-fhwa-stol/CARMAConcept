package gov.dot.fhwa.saxton.carmasecondary.utils;

import gov.dot.fhwa.saxton.carmasecondary.utils.AppConfig;

public class TestConfig extends AppConfig {
    private static class AppConfigHolder {
        private static final TestConfig instance_ = new TestConfig();
    }

    public static IAppConfig getInstance() { return AppConfigHolder.instance_; }

    public TestConfig() { }

    public void setProperty(String name, String value) {
        properties.setProperty(name, value);
    }
}
