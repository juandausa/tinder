package classes;

/**
 * Class that contains configuration constants.
 */
public final class Constants {

    /**
     * Ip of the server. Used to build paths for requests.
     */
    public static final String IP_SERVER = "http://10.1.105.93:5000"; //"http://10.0.2.2:5000"; //"http://192.168.1.106:5000";

    /**
     * Route for constructing the url path for the request that checks if the user is registered in
     * the app.
     */
    public static final String LOGIN_PATH = "/login/";

    /**
     * Route for constructing the url path for the request that register a new user in the app.
     */
    public static final String REGISTER_PATH = "/register/";

    /**
     * Route for constructing the url path for the request that gets the people that match with the
     * discovery filters.
     */
    public static final String CANDIDATES_PATH = "/candidates/";

    /**
     * Route for constructing the url path for the request that... TODO.
     */
    public static final String USER_DATA_PATH = "/user/";

    /**
     * Route for constructing the url path for the request that changes the filters of people
     * discovery.
     */
    public static final String FILTERS_PATH = "/filters/";


    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Private constructor of the class Constants.
     */
    private Constants() { }

}
