#include <string>
#include <vector>
#include <exception>
using namespace std;

#ifndef __ROADDataCollection_h__
#define __ROADDataCollection_h__

#include "IROADDataContainer.h"
 #include "IROADDataCollection.h"

namespace ROADEncoding
{
	class IROADDataContainer;
}
namespace ROADoverEncoding
{
	class IROADDataCollection;
	class ROADDataCollection;
}

namespace ROADoverEncoding
{
	class ROADDataCollection: public ROADoverEncoding::IROADDataCollection
	{
		private: unsigned int _count;
        private: std::vector<ROADEncoding::IROADDataContainer*> _container;

		public: unsigned int getCount();

        public: ROADEncoding::IROADDataContainer* getIROADDataContainer(unsigned int aIndex);

		public: void addIROADDataContainer(ROADEncoding::IROADDataContainer* aItem);

		public: void reset();
	};
}

#endif
