#include "CVSTools.h"
#include <iostream>

CVSTools::CVS::CVS(CVSConfiguration config)
{ this->config = config; }


void CVSTools::CVS::WriteFile(const char* data)
{ 
    cvsFile.open(std::string(config.dir) + std::string(config.filename) + ".csv"); 
    cvsFile << data;
    cvsFile.close();
}

CVSTools::CVSHandler::CVSHandler(CVSProperties* properties, CVSConfiguration config) : CVSTools::CVS::CVS(config)
{  
    this->properties = properties; 
    data = std::string();
    CVSHeaderParser();
}

CVSTools::CVSHandler::~CVSHandler()
{ delete properties; data.clear(); }

void CVSTools::CVSHandler::CVSParser(size_t headingIndex, const char* appendData)
{
    if(headingIndex == 0) data += '\n';
    data += appendData;
    if(headingIndex + 1 != properties->col) data += ',';
}

void CVSTools::CVSHandler::CVSStart()
{
    WriteFile(data.c_str());
}

void CVSTools::CVSHandler::CVSHeaderParser()
{
    for(size_t i = 0; i < properties->col; i++)
        {
            data += properties->headings[i];
            if(i + 1 != properties->col) data += ',';
        }
}

