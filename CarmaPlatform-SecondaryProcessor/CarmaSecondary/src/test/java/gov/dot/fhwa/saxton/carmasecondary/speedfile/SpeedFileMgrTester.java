package gov.dot.fhwa.saxton.carmasecondary.speedfile;

import java.util.List;
import org.junit.*;
import static org.junit.Assert.*;

import gov.dot.fhwa.saxton.carmasecondary.utils.*;
import gov.dot.fhwa.saxton.carmasecondary.speedfile.*;

public class SpeedFileMgrTester {
    private TestConfig config_ = null;
    private SpeedFileMgr mgr = null;

    @Before
    public void startup() {
        //create a custom app config so we don't have to use the production config file
        config_ = (TestConfig)TestConfig.getInstance();
        config_.setProperty("accel.initial", "1.3");
        config_.setProperty("speed.initial", "27");
        config_.setProperty("multilap.enable", "true");

        //create the test object for use in the following tests
        mgr = new SpeedFileMgr(config_);
    }

    @Test
    public void testSimpleFileLoad() {
        System.out.print("Testing simple file load...");
        try {
            List<Waypoint> wpl = mgr.parseCSV("testdata/SpeedProfileSimple.csv");
            assertEquals(3, wpl.size());
            assertEquals(552, wpl.get(0).getHeadway());
            assertEquals("label 3", wpl.get(2).getId());
            System.out.println("done");
        }catch (Exception e) {
            System.out.println("EXCEPTION TRAPPED: " + e.toString());
            assertTrue(false);
        }
    }

    @Test
    public void testComments() {
        System.out.print("Testing comments...");
        try {
            List<Waypoint> wpl = mgr.parseCSV("testdata/SpeedProfileComments.csv");
            assertEquals(5, wpl.size());
            assertEquals(16, (int)wpl.get(4).getSpeed());
            System.out.println("done");
        }catch (Exception e) {
            System.out.println("EXCEPTION TRAPPED: " + e.toString());
            assertTrue(false);
        }
    }

    @Test
    public void testOptionalFlags() {
        System.out.print("Testing option flags...");
        try {
            List<Waypoint> wpl = mgr.parseCSV("testdata/SpeedProfileOptionalFlags.csv");
            assertEquals(6, wpl.size());
            assertEquals(16, (int)wpl.get(4).getSpeed());
            System.out.print("sanity...");

            assertFalse(wpl.get(0).isSingleUse());
            assertTrue(wpl.get(0).isAvailable());
            System.out.print("0");

            assertTrue(wpl.get(1).isSingleUse());
            assertTrue(wpl.get(1).isAvailable());
            System.out.print("1");

            assertFalse(wpl.get(2).isSingleUse());
            assertTrue(wpl.get(2).isAvailable());
            System.out.print("2");

            assertFalse(wpl.get(3).isSingleUse());
            assertTrue(wpl.get(3).isAvailable());
            System.out.print("3");

            assertFalse(wpl.get(4).isSingleUse());
            assertTrue(wpl.get(4).isAvailable());
            System.out.print("4");

            assertTrue(wpl.get(5).isSingleUse());
            assertTrue(wpl.get(5).isAvailable());
            System.out.print("5...");
            System.out.println("done");

        }catch (Exception e) {
            System.out.println("EXCEPTION TRAPPED: " + e.toString());
            assertTrue(false);
        }
    }
}