package gov.dot.fhwa.saxton.carmasecondary.utils;

/**
 * Created by starkj on 2/18/2016.
 *
 * Defines an interface that each installable component (e.g. jar) can use to define its version ID.
 * It is suggested the implementing class be constructed as a singleton to ensure uniformity of info.
 *
 * This interface supports a definition of a version ID that may consist of the following elements:
 *      <component name> X.Y.Z.B<suffix>
 * where
 *      <component name> is the name of the component (e.g. jar file) identifying itself,
 *      X is the major revision number,
 *      Y is the minor revision number,
 *      Z and B are optional more-minor revision/build discriminators,
 *      <suffix> is an optional string that could further discriminate the build (e.g. "-RC1", "-TEST", etc).
 *
 * None of these elements is required to be used, but such a complex notation is supported.  Note
 * that some projects use very lengthy revision "numbers" with several decimals; only the first two
 * values are supported in this standard interface, but the implementing class could add methods to
 * store and retrieve each of those successive values (e.g. Z and B in this example).
 */
public interface IComponentVersion {

    /**
     * Provides a way to numerically compare the major revision ID (typically to the left of the decimal).
     * @return the major part of the revision "number"
     */
    public int majorRevision();

    /**
     * Provides a way to numerically compare the minor revision ID.  This is typically the first
     * number to the right of the first decimal (e.g. this would be Y in a version of X.Y.Z.B).
     * @return the minor part of the revision "number"
     */
    public int minorRevision();

    /**
     * @return The name of the component implementing this interface
     */
    public String componentName();

    /**
     * @return the full revision string (the "numerical" part of the ID)
     */
    public String revisionString();

    /**
     * @return the version suffix
     */
    public String suffix();

    /**
     * @return the full version ID of this component, including name and suffix, if any
     * Not intended to provide sub-component info.  For that use toStringWithDependencies().
     */
    public String toString();

    /**
     * @return the full version ID of this component plus the full string identifying all
     * of the components it depends upon.
     */
    public String toStringWithDependencies();
}
