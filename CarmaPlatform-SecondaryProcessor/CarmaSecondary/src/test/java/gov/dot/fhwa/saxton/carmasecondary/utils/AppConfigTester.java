package gov.dot.fhwa.saxton.carmasecondary.utils;

import gov.dot.fhwa.saxton.carmasecondary.utils.AppConfig;
import org.junit.*;
import static org.junit.Assert.*;

/**
 * Created by starkj on 2/19/2016.
 */
public class AppConfigTester {

    //can only do one test method because we have to guarantee that the first test is the file loading.
    //Doing that in a setup method just wouldn't be right because we need to verify its function.
    @Test
    public void testAll() {

        AppConfig config = (AppConfig)AppConfig.getInstance();

        //step 1 - attempting to load a non-existent file
        System.out.println("AppConfigTester: beginning step 1.");
        try {
            config.loadFile("nosuchfile");
            assertTrue(false);
        } catch (Exception e) {
            assertTrue(true);
        }

        //step 2 - attempt to load a real config file
        System.out.println("AppConfigTester: beginning step 2.");
        try {
            config.loadFile("testdata/testconfig.properties");
            assertTrue(true);
        }catch (Exception e){
            assertTrue(false);
        }

        //step 3-4 - test some string properties
        System.out.println("AppConfigTester: beginning step 3.");
        String res1 = config.getProperty("prop1");
        assertEquals(res1, "nothing");

        System.out.println("AppConfigTester: beginning step 4.");
        String res2 = config.getProperty("prop2");
        assertEquals(res2, "something");

        //step 5 - string at the bottom of the file
        System.out.println("AppConfigTester: beginning step 5.");
        String resf = config.getProperty("propfinal");
        assertEquals(resf, "finAL");

        //step 6 - look for a string that isn't there
        System.out.println("AppConfigTester: beginning step 6.");
        String resnot = config.getProperty("aintthere");
        assertEquals(resnot, null);

        //step 7 - integer with a decimal in the name
        System.out.println("AppConfigTester: beginning step 7.");
        int i1 = config.getIntValue("prop.int");
        assertEquals(14, i1);

        //step 8 - integer that exists with default value
        System.out.println("AppConfigTester: beginning step 8.");
        int i2 = config.getDefaultIntValue("prop.negint", 5);
        assertEquals(-29, i2);

        //step 9 - integer that doesn't exist with default value
        System.out.println("AppConfigTester: beginning step 9.");
        int i3 = config.getDefaultIntValue("aintthere", 6);
        assertEquals(6, i3);

        //step 10 - floating point value
        System.out.println("AppConfigTester: beginning step 10.");
        double d1 = Double.valueOf(config.getProperty("prop.real"));
        assertEquals(3.14567, d1, 0.00001);

        //step 11 - boolean value
        System.out.println("AppConfigTester: beginning step 11.");
        boolean b = config.getBooleanValue("prop.bool.ean");
        assertTrue(b);
    }

}
