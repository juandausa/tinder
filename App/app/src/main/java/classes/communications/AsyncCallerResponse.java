package classes.communications;


/**
 * Interface that exports the method to finish the process of load a bitmap
 */
@Deprecated
public interface AsyncCallerResponse {

    /**
     * Logic that execute when finishes the process of load a bitmap
     * @param data the data
     */
    public void processFinish(String data);
}
