using System.Net;

public static async Task<HttpResponseMessage> Run(HttpRequestMessage req, TraceWriter log)
{
    log.Info("C# HTTP trigger function processed a request.");

    // parse query parameter
    string message = req.GetQueryNameValuePairs()
        .FirstOrDefault(q => string.Compare(q.Key, "message", true) == 0)
        .Value;

    if (message == null)
    {
        // Get request body
        dynamic data = await req.Content.ReadAsAsync<object>();
        message = data?.message;
    }

    return message == null
        ? req.CreateResponse(HttpStatusCode.BadRequest, "Please pass a message on the query string or in the request body")
        : req.CreateResponse(HttpStatusCode.OK, message.ToUpper());
}
