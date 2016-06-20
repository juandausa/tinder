#include "GetMatchesController.h"



void GetMatchesController::operation(Request &request, Response &response) {
    response.SetCode(200);
    response.SetBody(this->fakeResponseForUserMatches());
    response.Send();
}

std::string GetMatchesController::fakeResponseForUserMatches() {
    Json::Value fakeInfo;
    Json::Value match, otherMatch;
    Json::Value message1, message2, message3, message4;
    match["user_id"] = "22";
    match["alias"] = "Josecito";
    match["age"] = "25";
    match["photo_profile"] = "";
    match["interests"] = Json::arrayValue;
    match["messages"] = Json::arrayValue;
    message1["0"] = "Hola, como estas?";
    message2["1"] = "Bien, y tu?";
    message3["1"] = "Que frio no?";
    match["messages"][0] = message1;
    match["messages"][1] = message2;
    match["messages"][2] = message3,
    otherMatch["user_id"] = "111";
    otherMatch["alias"] = "Juanita";
    otherMatch["age"] = "32";
    otherMatch["photo_profile"] = "";
    otherMatch["interests"] = Json::arrayValue;
    otherMatch["messages"] = Json::arrayValue;
    message4["0"] = "Hola, alguien ahi?";
    otherMatch["messages"][0] = message4;
    fakeInfo["matches"] = Json::arrayValue;
    fakeInfo["matches"][0] = match;
    fakeInfo["matches"][1] = otherMatch;
    return fastWriter.write(fakeInfo);
}