// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "WebResponder.hpp"

namespace teo
{

/************************************************************************/

bool WebResponder::read(yarp::os::ConnectionReader &in) {
    //-- Kind of boilerplate for mini web server
    yarp::os::Bottle got, response;
    if (!got.read(in)) return false;
    yarp::os::ConnectionWriter *out = in.getWriter();
    if (out==NULL) return true;
    response.addString("web");
    CD_INFO("Got: %s\n", got.toString().c_str());
    std::string page = got.get(0).asString();

    //-- Special page response (buttons.html)
    if (page=="buttons.html") {
        std::string buttonsString = readFile("buttons.html");
        std::vector<std::string> me = listFromDir("/home");
        for(int i=0;i<(int)me.size();i++)
        {
            CD_INFO("%s\n",me[i].c_str());
        }
        //buttonsString.replace();
        response.addString( buttonsString );
        //--Add logic here
        return response.write(*out);
    }

    //-- Default page response
    response.addString( readFile(page) );
    return response.write(*out);

    return true;
}

/************************************************************************/

std::string WebResponder::readFile(const std::string& fileName) {
    CD_DEBUG("fileName: %s\n",fileName.c_str());
    std::string searchString("html/");
    searchString += fileName;
    std::string fullName = rf->findFileByName(searchString);
    if( fullName == "" ) {
        std::string failResponse("[error] Could not find file \"");
        failResponse += fileName;
        failResponse += "\" on server.";
        CD_ERROR("%s",failResponse.c_str());
        return failResponse;
    }

    std::ifstream fileIfstream(fullName.c_str());
    if(!fileIfstream.is_open()) {
        std::string failResponse("[error] Could not open file \"");
        failResponse += fileName;
        failResponse += "\" at \"";
        failResponse += fullName;
        failResponse += "\" on server (contact a web admin, may lack file permission issue on server).";
        CD_ERROR("%s",failResponse.c_str());
        return failResponse;
    }

    //-- Pass input file to string.
    // [thanks:author] Tyler McHenry @ nerdland.net and KeithB @ ndssl.vbi.vt.edu
    // [thanks:link] http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring [2012-02-06]
    std::string successResponse;
    fileIfstream.seekg(0, std::ios::end);
    successResponse.reserve(fileIfstream.tellg());
    fileIfstream.seekg(0, std::ios::beg);
    successResponse.assign((std::istreambuf_iterator<char>(fileIfstream)),
                std::istreambuf_iterator<char>());
    fileIfstream.close();
    return successResponse;
}

/************************************************************************/

std::vector<std::string> WebResponder::listFromDir(const std::string& dirName) {
    CD_DEBUG("dirName: %s\n",dirName.c_str());
    DIR *dp;
    struct dirent *ep;
    dp = opendir( dirName.c_str() );
    if (dp == NULL) {
        CD_ERROR("Could not find directory \"%s\" on server.\n",dirName.c_str());
        std::vector<std::string> failResponse;
        return failResponse;
    }
    std::vector<std::string> successResponse;
    while (ep = readdir (dp)) {
        std::string fileName(ep->d_name);
        successResponse.push_back(fileName);
    }
    (void) closedir (dp);
    return successResponse;
}

/************************************************************************/

void WebResponder::setRf(yarp::os::ResourceFinder *value) {
    rf = value;
}

/************************************************************************/

}  // namespace teo

