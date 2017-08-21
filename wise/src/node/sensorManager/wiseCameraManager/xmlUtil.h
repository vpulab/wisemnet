/***************************************************************************
 *   xmlIO.h     - description
 *
 *   This program is part of the ETISEO project.
 *
 *   See http://www.etiseo.net  http://www.silogic.fr    
 *
 *   (C) Silogic - ETISEO Consortium
 ***************************************************************************/


#ifndef _ETI_XML_IO_H_
#define _ETI_XML_IO_H_

#include <ostream>
#include <istream>
#include <libxml/xmlIO.h>
#include <libxml/xmlwriter.h>


namespace Etiseo {

	//!  A function to handle libxml2 initialization
	class UtilXml
	{
		public:
		
			static void	Init();
			static void	Cleanup();
			
			static int ReadCallback(void * context, char * buffer, int length);
			static int InputCloseCallback(void * context);

			static int WriteCallback(void * context, const char * buffer, int length);
			static int OutputCloseCallback(void * context);
	};

	//!  mapping output from libxml2 to ostream
	class XmlOutputHandler 
	{
		public:
			
			XmlOutputHandler(std::ostream& stream);
			virtual ~XmlOutputHandler();
			
		int	write(const char* buffer, int length);
		int close(); 
		
		inline const struct _xmlOutputBuffer* xmlOutputBuffer() const 
			{ return mOutBuffer; }
		inline struct _xmlOutputBuffer* xmlOutputBuffer() { return mOutBuffer; }
		
		private:
			std::ostream					&mStream;
			struct _xmlOutputBuffer			*mOutBuffer; 
			
			
	};

	//!  mapping intput from libxml2 from istream
	class XmlInputHandler 
	{
		public:
			
			XmlInputHandler(std::istream& stream);
			virtual ~XmlInputHandler();
			
		int	read(char* buffer, int length);
		int close(); 
		
		inline const struct _xmlParserInputBuffer* xmlInputBuffer() const 
			{ return mInBuffer; }
		inline struct _xmlParserInputBuffer* xmlInputBuffer() { return mInBuffer; }
		
		private:
			std::istream					&mStream;
			struct _xmlParserInputBuffer	*mInBuffer; 
			
			
	};
	


};

#endif
