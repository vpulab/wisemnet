//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/wirelessChannel/WirelessChannelMessages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WirelessChannelMessages_m.h"

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

Register_Class(WirelessChannelSignalBegin);

WirelessChannelSignalBegin::WirelessChannelSignalBegin(const char *name, int kind) : ::omnetpp::cMessage(name,kind)
{
    this->nodeID = 0;
    this->power_dBm = 0;
    this->carrierFreq = 0;
    this->bandwidth = 0;
    this->modulationType = 0;
    this->encodingType = 0;
}

WirelessChannelSignalBegin::WirelessChannelSignalBegin(const WirelessChannelSignalBegin& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

WirelessChannelSignalBegin::~WirelessChannelSignalBegin()
{
}

WirelessChannelSignalBegin& WirelessChannelSignalBegin::operator=(const WirelessChannelSignalBegin& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void WirelessChannelSignalBegin::copy(const WirelessChannelSignalBegin& other)
{
    this->nodeID = other.nodeID;
    this->power_dBm = other.power_dBm;
    this->carrierFreq = other.carrierFreq;
    this->bandwidth = other.bandwidth;
    this->modulationType = other.modulationType;
    this->encodingType = other.encodingType;
}

void WirelessChannelSignalBegin::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->nodeID);
    doParsimPacking(b,this->power_dBm);
    doParsimPacking(b,this->carrierFreq);
    doParsimPacking(b,this->bandwidth);
    doParsimPacking(b,this->modulationType);
    doParsimPacking(b,this->encodingType);
}

void WirelessChannelSignalBegin::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->nodeID);
    doParsimUnpacking(b,this->power_dBm);
    doParsimUnpacking(b,this->carrierFreq);
    doParsimUnpacking(b,this->bandwidth);
    doParsimUnpacking(b,this->modulationType);
    doParsimUnpacking(b,this->encodingType);
}

int WirelessChannelSignalBegin::getNodeID() const
{
    return this->nodeID;
}

void WirelessChannelSignalBegin::setNodeID(int nodeID)
{
    this->nodeID = nodeID;
}

double WirelessChannelSignalBegin::getPower_dBm() const
{
    return this->power_dBm;
}

void WirelessChannelSignalBegin::setPower_dBm(double power_dBm)
{
    this->power_dBm = power_dBm;
}

double WirelessChannelSignalBegin::getCarrierFreq() const
{
    return this->carrierFreq;
}

void WirelessChannelSignalBegin::setCarrierFreq(double carrierFreq)
{
    this->carrierFreq = carrierFreq;
}

double WirelessChannelSignalBegin::getBandwidth() const
{
    return this->bandwidth;
}

void WirelessChannelSignalBegin::setBandwidth(double bandwidth)
{
    this->bandwidth = bandwidth;
}

int WirelessChannelSignalBegin::getModulationType() const
{
    return this->modulationType;
}

void WirelessChannelSignalBegin::setModulationType(int modulationType)
{
    this->modulationType = modulationType;
}

int WirelessChannelSignalBegin::getEncodingType() const
{
    return this->encodingType;
}

void WirelessChannelSignalBegin::setEncodingType(int encodingType)
{
    this->encodingType = encodingType;
}

class WirelessChannelSignalBeginDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WirelessChannelSignalBeginDescriptor();
    virtual ~WirelessChannelSignalBeginDescriptor();

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

Register_ClassDescriptor(WirelessChannelSignalBeginDescriptor);

WirelessChannelSignalBeginDescriptor::WirelessChannelSignalBeginDescriptor() : omnetpp::cClassDescriptor("WirelessChannelSignalBegin", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

WirelessChannelSignalBeginDescriptor::~WirelessChannelSignalBeginDescriptor()
{
    delete[] propertynames;
}

bool WirelessChannelSignalBeginDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WirelessChannelSignalBegin *>(obj)!=nullptr;
}

const char **WirelessChannelSignalBeginDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WirelessChannelSignalBeginDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WirelessChannelSignalBeginDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int WirelessChannelSignalBeginDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *WirelessChannelSignalBeginDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodeID",
        "power_dBm",
        "carrierFreq",
        "bandwidth",
        "modulationType",
        "encodingType",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int WirelessChannelSignalBeginDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeID")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "power_dBm")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "carrierFreq")==0) return base+2;
    if (fieldName[0]=='b' && strcmp(fieldName, "bandwidth")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "modulationType")==0) return base+4;
    if (fieldName[0]=='e' && strcmp(fieldName, "encodingType")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WirelessChannelSignalBeginDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
        "double",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **WirelessChannelSignalBeginDescriptor::getFieldPropertyNames(int field) const
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

const char *WirelessChannelSignalBeginDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WirelessChannelSignalBeginDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalBegin *pp = (WirelessChannelSignalBegin *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WirelessChannelSignalBeginDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalBegin *pp = (WirelessChannelSignalBegin *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodeID());
        case 1: return double2string(pp->getPower_dBm());
        case 2: return double2string(pp->getCarrierFreq());
        case 3: return double2string(pp->getBandwidth());
        case 4: return long2string(pp->getModulationType());
        case 5: return long2string(pp->getEncodingType());
        default: return "";
    }
}

bool WirelessChannelSignalBeginDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalBegin *pp = (WirelessChannelSignalBegin *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodeID(string2long(value)); return true;
        case 1: pp->setPower_dBm(string2double(value)); return true;
        case 2: pp->setCarrierFreq(string2double(value)); return true;
        case 3: pp->setBandwidth(string2double(value)); return true;
        case 4: pp->setModulationType(string2long(value)); return true;
        case 5: pp->setEncodingType(string2long(value)); return true;
        default: return false;
    }
}

const char *WirelessChannelSignalBeginDescriptor::getFieldStructName(int field) const
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

void *WirelessChannelSignalBeginDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalBegin *pp = (WirelessChannelSignalBegin *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WirelessChannelSignalEnd);

WirelessChannelSignalEnd::WirelessChannelSignalEnd(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->nodeID = 0;
}

WirelessChannelSignalEnd::WirelessChannelSignalEnd(const WirelessChannelSignalEnd& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

WirelessChannelSignalEnd::~WirelessChannelSignalEnd()
{
}

WirelessChannelSignalEnd& WirelessChannelSignalEnd::operator=(const WirelessChannelSignalEnd& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void WirelessChannelSignalEnd::copy(const WirelessChannelSignalEnd& other)
{
    this->nodeID = other.nodeID;
}

void WirelessChannelSignalEnd::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->nodeID);
}

void WirelessChannelSignalEnd::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->nodeID);
}

int WirelessChannelSignalEnd::getNodeID() const
{
    return this->nodeID;
}

void WirelessChannelSignalEnd::setNodeID(int nodeID)
{
    this->nodeID = nodeID;
}

class WirelessChannelSignalEndDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WirelessChannelSignalEndDescriptor();
    virtual ~WirelessChannelSignalEndDescriptor();

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

Register_ClassDescriptor(WirelessChannelSignalEndDescriptor);

WirelessChannelSignalEndDescriptor::WirelessChannelSignalEndDescriptor() : omnetpp::cClassDescriptor("WirelessChannelSignalEnd", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

WirelessChannelSignalEndDescriptor::~WirelessChannelSignalEndDescriptor()
{
    delete[] propertynames;
}

bool WirelessChannelSignalEndDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WirelessChannelSignalEnd *>(obj)!=nullptr;
}

const char **WirelessChannelSignalEndDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WirelessChannelSignalEndDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WirelessChannelSignalEndDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WirelessChannelSignalEndDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WirelessChannelSignalEndDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodeID",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WirelessChannelSignalEndDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeID")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WirelessChannelSignalEndDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WirelessChannelSignalEndDescriptor::getFieldPropertyNames(int field) const
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

const char *WirelessChannelSignalEndDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WirelessChannelSignalEndDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalEnd *pp = (WirelessChannelSignalEnd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WirelessChannelSignalEndDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalEnd *pp = (WirelessChannelSignalEnd *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodeID());
        default: return "";
    }
}

bool WirelessChannelSignalEndDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalEnd *pp = (WirelessChannelSignalEnd *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodeID(string2long(value)); return true;
        default: return false;
    }
}

const char *WirelessChannelSignalEndDescriptor::getFieldStructName(int field) const
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

void *WirelessChannelSignalEndDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelSignalEnd *pp = (WirelessChannelSignalEnd *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WirelessChannelNodeMoveMessage);

WirelessChannelNodeMoveMessage::WirelessChannelNodeMoveMessage(const char *name, int kind) : ::omnetpp::cMessage(name,kind)
{
    this->nodeID = 0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->phi = 0;
    this->theta = 0;
}

WirelessChannelNodeMoveMessage::WirelessChannelNodeMoveMessage(const WirelessChannelNodeMoveMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

WirelessChannelNodeMoveMessage::~WirelessChannelNodeMoveMessage()
{
}

WirelessChannelNodeMoveMessage& WirelessChannelNodeMoveMessage::operator=(const WirelessChannelNodeMoveMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void WirelessChannelNodeMoveMessage::copy(const WirelessChannelNodeMoveMessage& other)
{
    this->nodeID = other.nodeID;
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
    this->phi = other.phi;
    this->theta = other.theta;
}

void WirelessChannelNodeMoveMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->nodeID);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->y);
    doParsimPacking(b,this->z);
    doParsimPacking(b,this->phi);
    doParsimPacking(b,this->theta);
}

void WirelessChannelNodeMoveMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->nodeID);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->y);
    doParsimUnpacking(b,this->z);
    doParsimUnpacking(b,this->phi);
    doParsimUnpacking(b,this->theta);
}

int WirelessChannelNodeMoveMessage::getNodeID() const
{
    return this->nodeID;
}

void WirelessChannelNodeMoveMessage::setNodeID(int nodeID)
{
    this->nodeID = nodeID;
}

double WirelessChannelNodeMoveMessage::getX() const
{
    return this->x;
}

void WirelessChannelNodeMoveMessage::setX(double x)
{
    this->x = x;
}

double WirelessChannelNodeMoveMessage::getY() const
{
    return this->y;
}

void WirelessChannelNodeMoveMessage::setY(double y)
{
    this->y = y;
}

double WirelessChannelNodeMoveMessage::getZ() const
{
    return this->z;
}

void WirelessChannelNodeMoveMessage::setZ(double z)
{
    this->z = z;
}

double WirelessChannelNodeMoveMessage::getPhi() const
{
    return this->phi;
}

void WirelessChannelNodeMoveMessage::setPhi(double phi)
{
    this->phi = phi;
}

double WirelessChannelNodeMoveMessage::getTheta() const
{
    return this->theta;
}

void WirelessChannelNodeMoveMessage::setTheta(double theta)
{
    this->theta = theta;
}

class WirelessChannelNodeMoveMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WirelessChannelNodeMoveMessageDescriptor();
    virtual ~WirelessChannelNodeMoveMessageDescriptor();

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

Register_ClassDescriptor(WirelessChannelNodeMoveMessageDescriptor);

WirelessChannelNodeMoveMessageDescriptor::WirelessChannelNodeMoveMessageDescriptor() : omnetpp::cClassDescriptor("WirelessChannelNodeMoveMessage", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

WirelessChannelNodeMoveMessageDescriptor::~WirelessChannelNodeMoveMessageDescriptor()
{
    delete[] propertynames;
}

bool WirelessChannelNodeMoveMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WirelessChannelNodeMoveMessage *>(obj)!=nullptr;
}

const char **WirelessChannelNodeMoveMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WirelessChannelNodeMoveMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WirelessChannelNodeMoveMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int WirelessChannelNodeMoveMessageDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *WirelessChannelNodeMoveMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nodeID",
        "x",
        "y",
        "z",
        "phi",
        "theta",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int WirelessChannelNodeMoveMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeID")==0) return base+0;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+1;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+2;
    if (fieldName[0]=='z' && strcmp(fieldName, "z")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "phi")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "theta")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WirelessChannelNodeMoveMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "double",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **WirelessChannelNodeMoveMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *WirelessChannelNodeMoveMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WirelessChannelNodeMoveMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelNodeMoveMessage *pp = (WirelessChannelNodeMoveMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WirelessChannelNodeMoveMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelNodeMoveMessage *pp = (WirelessChannelNodeMoveMessage *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNodeID());
        case 1: return double2string(pp->getX());
        case 2: return double2string(pp->getY());
        case 3: return double2string(pp->getZ());
        case 4: return double2string(pp->getPhi());
        case 5: return double2string(pp->getTheta());
        default: return "";
    }
}

bool WirelessChannelNodeMoveMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelNodeMoveMessage *pp = (WirelessChannelNodeMoveMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setNodeID(string2long(value)); return true;
        case 1: pp->setX(string2double(value)); return true;
        case 2: pp->setY(string2double(value)); return true;
        case 3: pp->setZ(string2double(value)); return true;
        case 4: pp->setPhi(string2double(value)); return true;
        case 5: pp->setTheta(string2double(value)); return true;
        default: return false;
    }
}

const char *WirelessChannelNodeMoveMessageDescriptor::getFieldStructName(int field) const
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

void *WirelessChannelNodeMoveMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WirelessChannelNodeMoveMessage *pp = (WirelessChannelNodeMoveMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


