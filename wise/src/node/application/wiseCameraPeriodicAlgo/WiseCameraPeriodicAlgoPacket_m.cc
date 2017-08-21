//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/application/wiseCameraPeriodicAlgo/WiseCameraPeriodicAlgoPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseCameraPeriodicAlgoPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(WiseCameraPeriodicAlgoPacket);

WiseCameraPeriodicAlgoPacket::WiseCameraPeriodicAlgoPacket(const char *name, int kind) : ::WiseApplicationPacket(name,kind)
{
    this->trackingCount = 0;
    this->targetID = 0;
    this->positionX = 0;
    this->positionY = 0;
    this->TypeNeighbour = 0;
}

WiseCameraPeriodicAlgoPacket::WiseCameraPeriodicAlgoPacket(const WiseCameraPeriodicAlgoPacket& other) : ::WiseApplicationPacket(other)
{
    copy(other);
}

WiseCameraPeriodicAlgoPacket::~WiseCameraPeriodicAlgoPacket()
{
}

WiseCameraPeriodicAlgoPacket& WiseCameraPeriodicAlgoPacket::operator=(const WiseCameraPeriodicAlgoPacket& other)
{
    if (this==&other) return *this;
    ::WiseApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void WiseCameraPeriodicAlgoPacket::copy(const WiseCameraPeriodicAlgoPacket& other)
{
    this->trackingCount = other.trackingCount;
    this->targetID = other.targetID;
    this->positionX = other.positionX;
    this->positionY = other.positionY;
    this->TypeNeighbour = other.TypeNeighbour;
}

void WiseCameraPeriodicAlgoPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WiseApplicationPacket::parsimPack(b);
    doParsimPacking(b,this->trackingCount);
    doParsimPacking(b,this->targetID);
    doParsimPacking(b,this->positionX);
    doParsimPacking(b,this->positionY);
    doParsimPacking(b,this->TypeNeighbour);
}

void WiseCameraPeriodicAlgoPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WiseApplicationPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->trackingCount);
    doParsimUnpacking(b,this->targetID);
    doParsimUnpacking(b,this->positionX);
    doParsimUnpacking(b,this->positionY);
    doParsimUnpacking(b,this->TypeNeighbour);
}

unsigned long WiseCameraPeriodicAlgoPacket::getTrackingCount() const
{
    return this->trackingCount;
}

void WiseCameraPeriodicAlgoPacket::setTrackingCount(unsigned long trackingCount)
{
    this->trackingCount = trackingCount;
}

unsigned int WiseCameraPeriodicAlgoPacket::getTargetID() const
{
    return this->targetID;
}

void WiseCameraPeriodicAlgoPacket::setTargetID(unsigned int targetID)
{
    this->targetID = targetID;
}

double WiseCameraPeriodicAlgoPacket::getPositionX() const
{
    return this->positionX;
}

void WiseCameraPeriodicAlgoPacket::setPositionX(double positionX)
{
    this->positionX = positionX;
}

double WiseCameraPeriodicAlgoPacket::getPositionY() const
{
    return this->positionY;
}

void WiseCameraPeriodicAlgoPacket::setPositionY(double positionY)
{
    this->positionY = positionY;
}

unsigned int WiseCameraPeriodicAlgoPacket::getTypeNeighbour() const
{
    return this->TypeNeighbour;
}

void WiseCameraPeriodicAlgoPacket::setTypeNeighbour(unsigned int TypeNeighbour)
{
    this->TypeNeighbour = TypeNeighbour;
}

class WiseCameraPeriodicAlgoPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseCameraPeriodicAlgoPacketDescriptor();
    virtual ~WiseCameraPeriodicAlgoPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(WiseCameraPeriodicAlgoPacketDescriptor);

WiseCameraPeriodicAlgoPacketDescriptor::WiseCameraPeriodicAlgoPacketDescriptor() : omnetpp::cClassDescriptor("WiseCameraPeriodicAlgoPacket", "WiseApplicationPacket")
{
    propertynames = nullptr;
}

WiseCameraPeriodicAlgoPacketDescriptor::~WiseCameraPeriodicAlgoPacketDescriptor()
{
    delete[] propertynames;
}

bool WiseCameraPeriodicAlgoPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseCameraPeriodicAlgoPacket *>(obj)!=nullptr;
}

const char **WiseCameraPeriodicAlgoPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseCameraPeriodicAlgoPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseCameraPeriodicAlgoPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int WiseCameraPeriodicAlgoPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *WiseCameraPeriodicAlgoPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "trackingCount",
        "targetID",
        "positionX",
        "positionY",
        "TypeNeighbour",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int WiseCameraPeriodicAlgoPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trackingCount")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetID")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionX")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionY")==0) return base+3;
    if (fieldName[0]=='T' && strcmp(fieldName, "TypeNeighbour")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseCameraPeriodicAlgoPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned long",
        "unsigned int",
        "double",
        "double",
        "unsigned int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseCameraPeriodicAlgoPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *WiseCameraPeriodicAlgoPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int WiseCameraPeriodicAlgoPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseCameraPeriodicAlgoPacket *pp = (WiseCameraPeriodicAlgoPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseCameraPeriodicAlgoPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraPeriodicAlgoPacket *pp = (WiseCameraPeriodicAlgoPacket *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getTrackingCount());
        case 1: return ulong2string(pp->getTargetID());
        case 2: return double2string(pp->getPositionX());
        case 3: return double2string(pp->getPositionY());
        case 4: return ulong2string(pp->getTypeNeighbour());
        default: return "";
    }
}

bool WiseCameraPeriodicAlgoPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseCameraPeriodicAlgoPacket *pp = (WiseCameraPeriodicAlgoPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setTrackingCount(string2ulong(value)); return true;
        case 1: pp->setTargetID(string2ulong(value)); return true;
        case 2: pp->setPositionX(string2double(value)); return true;
        case 3: pp->setPositionY(string2double(value)); return true;
        case 4: pp->setTypeNeighbour(string2ulong(value)); return true;
        default: return false;
    }
}

const char *WiseCameraPeriodicAlgoPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *WiseCameraPeriodicAlgoPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraPeriodicAlgoPacket *pp = (WiseCameraPeriodicAlgoPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


