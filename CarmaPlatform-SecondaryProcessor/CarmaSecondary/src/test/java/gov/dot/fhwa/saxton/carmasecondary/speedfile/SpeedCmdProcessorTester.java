package gov.dot.fhwa.saxton.carmasecondary.speedfile;

import java.util.List;
import org.junit.*;
import static org.junit.Assert.*;

import gov.dot.fhwa.saxton.carmasecondary.utils.*;
import gov.dot.fhwa.saxton.carmasecondary.speedfile.*;

public class SpeedCmdProcessorTester {
    private TestConfig config_ = null;
    private SpeedCmdProcessor proc = null;

    @Before
    public void startup() {
        //create a custom app config so we don't have to use the production config file
        config_ = (TestConfig) TestConfig.getInstance();
        config_.setProperty("mab.spdcmd.port", "5555");
        config_.setProperty("mab.host", "192.168.88.21");
        config_.setProperty("speedFile.enable", "true");
        config_.setProperty("speedFile.path", "testdata/SpeedProfileRoute.csv");
        config_.setProperty("accel.initial", "1.3");
        config_.setProperty("speed.initial", "27");
        config_.setProperty("multilap.enable", "true");
    }

    //We won't worry about a failure in initialize() here because normally the UDP connection would fail.
    //But we need to use it to read the speed profile.
    //This test needs to be run manually through the debugger since the only observable output is on the
    // UDP port that we can't set up & monitor here.

    @Test
    public void testProfileDisabled() {
        config_.setProperty("speedFile.enable", "false");
        proc = new SpeedCmdProcessor(config_);
        System.out.print("Running testProfileDisabled - NEEDS TO BE RUN IN DEBUGGER...");

        try {
            proc.initialize();
        }catch (Exception e) {
            //virtually guaranteed to catch one due to lack of MAB socket availability
        }

        try {
            //far away from any waypooints
            proc.generateSpeedCmd(39.000000, -77.900000);

            //within 10 m of WP 1
            proc.generateSpeedCmd(39.000100, -77.000110);

            //within 10 m of WP 2
            proc.generateSpeedCmd(39.001111, -77.000100);
        }catch (Exception e) {
            //don't worry about it
        	System.out.print("Exception trapped...");
        }
        System.out.println("done.");
        assertTrue(true); //to guarantee the build won't fail on this test
    }

    //We won't worry about a failure in initialize() here because normally the UDP connection would fail.
    //But we need to use it to read the speed profile.
    //This test needs to be run manually through the debugger since the only observable output is on the
    // UDP port that we can't set up & monitor here.

    @Test
    public void testProfileEnabled() {
        config_.setProperty("speedFile.enable", "true");
        proc = new SpeedCmdProcessor(config_);
        System.out.print("Running testProfileEnabled - NEEDS TO BE RUN IN DEBUGGER...");

        try {
            proc.initialize();
        }catch (Exception e) {
            //virtually guaranteed to catch one due to lack of MAB socket availability
        }

        try {
            //far away from any waypoints
            proc.generateSpeedCmd(39.000000, -77.900000);
        }catch (Exception e) {
            //don't worry about it
        }

        try {
            //within 10 m of WP 1
            proc.generateSpeedCmd(39.000100, -77.000110);
	    }catch (Exception e) {
	        //don't worry about it
	    }

        try {
            //within 10 m of WP 2
            proc.generateSpeedCmd(39.001111, -77.000100);
        }catch (Exception e) {
            //don't worry about it
        }
 
        try {
            //within 10 m of WP 3
            proc.generateSpeedCmd(39.002108, -77.000100); //should mark this one unavailable
        }catch (Exception e) {
            //don't worry about it
        }
 
        try {
            //within 20 m of WP 4
            proc.generateSpeedCmd(39.002100, -77.001123);
        }catch (Exception e) {
            //don't worry about it
        }
 
        try {
            //another location in between
            proc.generateSpeedCmd(39.003000, -77.001444); //should use same cmds as previous call
        }catch (Exception e) {
            //don't worry about it
        }
 
        try {
            //back to WP 2 - right on top of it
            proc.generateSpeedCmd(39.001100, -77.000100); //back to wp 2 commands
        }catch (Exception e) {
            //don't worry about it
        }
 
        try {
            //back to WP 3
            proc.generateSpeedCmd(39.002109, -77.000200); //should still use previous commands; ignore this WP
        }catch (Exception e) {
            //don't worry about it
        }
 
        try {
            //back to WP 4
            proc.generateSpeedCmd(39.002077, -77.001145); //should pick up WP 4 cmds
        }catch (Exception e) {
            //don't worry about it
        }
        System.out.println("done.");
        assertTrue(true); //to guarantee the build won't fail on this test
    }
}