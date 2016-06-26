package classes;

import org.json.JSONObject;

/**
 * Class that represents a candidate to be a match with the current user.
 */
public class CandidateData extends UserData {

    /**
     * Constructor of the class CandidateData
     *
     * @param candidate the JSONObject containing the candidate data.
     */
    public CandidateData(JSONObject candidate) {
        super(candidate);
    }
}
