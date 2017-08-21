//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/application/wiseCameraTrackerTest/WiseCameraTrackerTestMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseCameraTrackerTestMessage_m.h"

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

Register_Class(WiseCameraTrackerTestMessage);

WiseCameraTrackerTestMessage::WiseCameraTrackerTestMessage(const char *name, int kind) : ::WiseApplicationPacket(name,kind)
{
    this->trackingCount = 0;
    this->targetID = 0;
    this->positionX = 0;
    this->positionY = 0;
}

WiseCameraTrackerTestMessage::WiseCameraTrackerTestMessage(const WiseCameraTrackerTestMessage& other) : ::WiseApplicationPacket(other)
{
    copy(other);
}

WiseCameraTrackerTestMessage::~WiseCameraTrackerTestMessage()
{
}

WiseCameraTrackerTestMessage& WiseCameraTrackerTestMessage::operator=(const WiseCameraTrackerTestMessage& other)
{
    if (this==&other) return *this;
    ::WiseApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void WiseCameraTrackerTestMessage::copy(const WiseCameraTrackerTestMessage& other)
{
    this->trackingCount = other.trackingCount;
    this->targetID = other.targetID;
    this->positionX = other.positionX;
    this->positionY = other.positionY;
}

void WiseCameraTrackerTestMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WiseApplicationPacket::parsimPack(b);
    doParsimPacking(b,this->trackingCount);
    doParsimPacking(b,this->targetID);
    doParsimPacking(b,this->positionX);
    doParsimPacking(b,this->positionY);
}

void WiseCameraTrackerTestMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WiseApplicationPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->trackingCount);
    doParsimUnpacking(b,this->targetID);
    doParsimUnpacking(b,this->positionX);
    doParsimUnpacking(b,this->positionY);
}

unsigned long WiseCameraTrackerTestMessage::getTrackingCount() const
{
    return this->trackingCount;
}

void WiseCameraTrackerTestMessage::setTrackingCount(unsigned long trackingCount)
{
    this->trackingCount = trackingCount;
}

unsigned int WiseCameraTrackerTestMessage::getTargetID() const
{
    return this->targetID;
}

void WiseCameraTrackerTestMessage::setTargetID(unsigned int targetID)
{
    this->targetID = targetID;
}

double WiseCameraTrackerTestMessage::getPositionX() const
{
    return this->positionX;
}

void WiseCameraTrackerTestMessage::setPositionX(double positionX)
{
    this->positionX = positionX;
}

double WiseCameraTrackerTestMessage::getPositionY() const
{
    return this->positionY;
}

void WiseCameraTrackerTestMessage::setPositionY(double positionY)
{
    this->positionY = positionY;
}

class WiseCameraTrackerTestMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseCameraTrackerTestMessageDescriptor();
    virtual ~WiseCameraTrackerTestMessageDescriptor();

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

Register_ClassDescriptor(WiseCameraTrackerTestMessageDescriptor);

WiseCameraTrackerTestMessageDescriptor::WiseCameraTrackerTestMessageDescriptor() : omnetpp::cClassDescriptor("WiseCameraTrackerTestMessage", "WiseApplicationPacket")
{
    propertynames = nullptr;
}

WiseCameraTrackerTestMessageDescriptor::~WiseCameraTrackerTestMessageDescriptor()
{
    delete[] propertynames;
}

bool WiseCameraTrackerTestMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseCameraTrackerTestMessage *>(obj)!=nullptr;
}

const char **WiseCameraTrackerTestMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseCameraTrackerTestMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseCameraTrackerTestMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int WiseCameraTrackerTestMessageDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *WiseCameraTrackerTestMessageDescriptor::getFieldName(int field) const
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
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int WiseCameraTrackerTestMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trackingCount")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetID")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionX")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionY")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseCameraTrackerTestMessageDescriptor::getFieldTypeString(int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseCameraTrackerTestMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseCameraTrackerTestMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseCameraTrackerTestMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseCameraTrackerTestMessage *pp = (WiseCameraTrackerTestMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseCameraTrackerTestMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraTrackerTestMessage *pp = (WiseCameraTrackerTestMessage *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getTrackingCount());
        case 1: return ulong2string(pp->getTargetID());
        case 2: return double2string(pp->getPositionX());
        case 3: return double2string(pp->getPositionY());
        default: return "";
    }
}

bool WiseCameraTrackerTestMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseCameraTrackerTestMessage *pp = (WiseCameraTrackerTestMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setTrackingCount(string2ulong(value)); return true;
        case 1: pp->setTargetID(string2ulong(value)); return true;
        case 2: pp->setPositionX(string2double(value)); return true;
        case 3: pp->setPositionY(string2double(value)); return true;
        default: return false;
    }
}

const char *WiseCameraTrackerTestMessageDescriptor::getFieldStructName(int field) const
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

void *WiseCameraTrackerTestMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraTrackerTestMessage *pp = (WiseCameraTrackerTestMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


