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
 * Created by fabrizio on 04/04/16.
 */
public class StatusRequest extends Request<Integer> {

    private Response.Listener mListener;

    /**********************************************************************************************/
    /**********************************************************************************************/

    public StatusRequest(int method, String url, Response.Listener listener, Response.ErrorListener errorListener) {
        super(method, url, errorListener);
        this.mListener = listener;
    }

    /**********************************************************************************************/
    /**********************************************************************************************/

    @Override
    protected Response<Integer> parseNetworkResponse(NetworkResponse response) {;
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

    @Override
    protected void deliverResponse(Integer response) {
        mListener.onResponse(response);
    }



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

        final long cacheHitButRefreshed = 3 * 60 * 1000; // in 3 minutes cache will be hit, but also refreshed on background
        final long cacheExpired = 24 * 60 * 60 * 1000; // in 24 hours this cache entry expires completely
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
