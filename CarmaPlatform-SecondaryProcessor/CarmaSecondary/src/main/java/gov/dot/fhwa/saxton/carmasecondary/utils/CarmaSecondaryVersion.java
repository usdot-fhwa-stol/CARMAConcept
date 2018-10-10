package gov.dot.fhwa.saxton.carmasecondary.utils;

/**
 * Makes available version info identifying the Carma Secondary component.
 */
public class CarmaSecondaryVersion implements IComponentVersion {

    ///// singleton management

    private CarmaSecondaryVersion() { }

    private static class ComponentVersionHolder {
        private static final CarmaSecondaryVersion _instance = new CarmaSecondaryVersion();
    }

    public static CarmaSecondaryVersion getInstance()
    {
        return ComponentVersionHolder._instance;
    }


    ///// Version info for the CarmaSecondary component

    private static final String name = "CarmaSecondary";
    private static final String suffix = "T1";
    private static final String revisionString = "2.2";
    private static final int majorRev = 2;
    private static final int minorRev = 2;

    public int majorRevision() { return majorRev; }

    public int minorRevision() { return minorRev; }

    public String componentName() { return name; }

    public String revisionString() { return revisionString; }

    public String suffix() { return suffix; }

    /**
     * Provides a string that describes the full version info for this component.
     * However, it does not address any dependency component.
     * @return
     */
    @Override
    public String toString() {
        return name + " " + revisionString + suffix;
    }

    public String toStringWithDependencies() {
        //this version of Carma has no local dependencies
        return toString();
    }

}
