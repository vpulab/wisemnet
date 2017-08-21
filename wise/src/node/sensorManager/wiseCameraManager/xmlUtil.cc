/***************************************************************************
 *   xmlIO.cpp   - description
 *
 *   This program is part of the Etiseo project.
 *
 *   See http://www.etiseo.net  http://www.silogic.fr   
 *
 *   (C) Silogic - Etiseo Consortium
 ***************************************************************************/

#include "xmlUtil.h"

using namespace Etiseo;


void UtilXml::Init()
{
	LIBXML_TEST_VERSION
	xmlKeepBlanksDefault(0);
	xmlSetExternalEntityLoader(xmlNoNetExternalEntityLoader);
}

void UtilXml::Cleanup()
{
	xmlCleanupParser();

}

/******************************************************************************************
*
* Output to ostream
*
******************************************************************************************/

int UtilXml::WriteCallback(void * context, const char * buffer, int length)
{
	XmlOutputHandler* handler = (XmlOutputHandler*)context;
	return handler->write(buffer,length);
}

int UtilXml::OutputCloseCallback(void * obj)
{
	XmlOutputHandler* handler = (XmlOutputHandler*)obj;
	return handler->close();
}

XmlOutputHandler::XmlOutputHandler(std::ostream& stream): mStream(stream)
{
	mOutBuffer = xmlOutputBufferCreateIO(UtilXml::WriteCallback, 
			UtilXml::OutputCloseCallback,
			this, NULL); 
}

XmlOutputHandler::~XmlOutputHandler()
{
	close();
	mOutBuffer = 0;
}

int XmlOutputHandler::write(const char* buffer, int length)
{
	mStream.write(buffer,length);
	return length;
}

int XmlOutputHandler::close()
{
	mStream.flush();
	return 0;
}

/******************************************************************************************
*
* Input from istream
*
******************************************************************************************/

int UtilXml::ReadCallback(void * context, char * buffer, int length)
{
	std::istream * is = (std::istream *)context;
	
	is->read(buffer,length);
	int size= is->gcount();
	if (size < length)
		buffer[size] = '\0';
		
	return size;
}

int UtilXml::InputCloseCallback(void * obj)
{
	XmlInputHandler* handler = (XmlInputHandler*)obj;
	return handler->close();
}


XmlInputHandler::XmlInputHandler(std::istream& stream) : mStream(stream)
{
	mInBuffer = xmlParserInputBufferCreateIO(UtilXml::ReadCallback,
				UtilXml::InputCloseCallback,
				this, XML_CHAR_ENCODING_NONE);
}

XmlInputHandler::~XmlInputHandler()
{
	close();
	mInBuffer = 0;
}

int XmlInputHandler::read(char* buffer, int length)
{
	mStream.read(buffer,length);
	return length;
}

int XmlInputHandler::close()
{
	return 0;
}



