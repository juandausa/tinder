package requests;

import android.util.Log;

import com.android.volley.Cache;
import com.android.volley.NetworkResponse;
import com.android.volley.ParseError;
import com.android.volley.Request;
import com.android.volley.Response;
import com.android.volley.toolbox.HttpHeaderParser;

import java.util.Map;

/**
 * Request that sends nothing and receives a response code
 */
public class StatusRequest extends Request<Integer> {

    private Response.Listener mListener;

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Constructor of the class StatusRequest
     * @param method the method to be used in the request (GET, POST, PUT, etc)
     * @param url the url where the request will be sent
     * @param listener the response listener
     * @param errorListener the error listener
     */
    public StatusRequest(int method, String url, Response.Listener listener,
                         Response.ErrorListener errorListener) {
        super(method, url, errorListener);
        this.mListener = listener;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Parse the the response of the request and returns it.
     * @param response the response of the request
     * @return the status code of the response to the request
     */
    @Override
    protected Response<Integer> parseNetworkResponse(NetworkResponse response) {
        try {
            Log.d("HEADERS", "Response Header = " + response.headers);
            Log.d("STATUS CODE", Integer.toString(response.statusCode));
            //Cache.Entry entry = HttpHeaderParser.parseCacheHeaders(response);
            //Cache.Entry entry = parseIgnoreCacheHeaders(response);
            Response<Integer> resp = Response.success(response.statusCode, null);
            return resp;
        } catch (Exception e) {
            return Response.error(new ParseError(e));
        }
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Deliver the response to the response listener
     * @param response the response to the request sent
     */
    @Override
    protected void deliverResponse(Integer response) {
        mListener.onResponse(response);
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    /**
     * Extracts a {@link Cache.Entry} from a {@link NetworkResponse}.
     * Cache-control headers are ignored. SoftTtl == 3 mins, ttl == 24 hours.
     * @param response The network response to parse headers from
     * @return a cache entry for the given response, or null if the response is not cacheable.
     */
    public static Cache.Entry parseIgnoreCacheHeaders(NetworkResponse response) {
        long now = System.currentTimeMillis();

        Map<String, String> headers = response.headers;
        long serverDate = 0;
        String serverEtag = null;
        String headerValue;

        headerValue = headers.get("Date");
        if (headerValue != null) {
            serverDate = HttpHeaderParser.parseDateAsEpoch(headerValue);
        }

        serverEtag = headers.get("ETag");

        // in 3 minutes cache will be hit, but also refreshed on background
        final long cacheHitButRefreshed = 3 * 60 * 1000;
        // in 24 hours this cache entry expires completely
        final long cacheExpired = 24 * 60 * 60 * 1000;
        final long softExpire = now + cacheHitButRefreshed;
        final long ttl = now + cacheExpired;

        Cache.Entry entry = new Cache.Entry();
        entry.data = response.data;
        entry.etag = serverEtag;
        entry.softTtl = softExpire;
        entry.ttl = ttl;
        entry.serverDate = serverDate;
        entry.responseHeaders = headers;

        return entry;
    }

}
