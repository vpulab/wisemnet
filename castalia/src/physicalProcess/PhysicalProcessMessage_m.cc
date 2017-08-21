//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/physicalProcess/PhysicalProcessMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "PhysicalProcessMessage_m.h"

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

Register_Class(PhysicalProcessMessage);

PhysicalProcessMessage::PhysicalProcessMessage(const char *name, int kind) : ::omnetpp::cMessage(name,kind)
{
    this->value = 0;
    this->xCoor = 0;
    this->yCoor = 0;
    this->srcID = 0;
    this->sensorIndex = 0;
}

PhysicalProcessMessage::PhysicalProcessMessage(const PhysicalProcessMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PhysicalProcessMessage::~PhysicalProcessMessage()
{
}

PhysicalProcessMessage& PhysicalProcessMessage::operator=(const PhysicalProcessMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PhysicalProcessMessage::copy(const PhysicalProcessMessage& other)
{
    this->value = other.value;
    this->xCoor = other.xCoor;
    this->yCoor = other.yCoor;
    this->srcID = other.srcID;
    this->sensorIndex = other.sensorIndex;
}

void PhysicalProcessMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->value);
    doParsimPacking(b,this->xCoor);
    doParsimPacking(b,this->yCoor);
    doParsimPacking(b,this->srcID);
    doParsimPacking(b,this->sensorIndex);
}

void PhysicalProcessMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->value);
    doParsimUnpacking(b,this->xCoor);
    doParsimUnpacking(b,this->yCoor);
    doParsimUnpacking(b,this->srcID);
    doParsimUnpacking(b,this->sensorIndex);
}

double PhysicalProcessMessage::getValue() const
{
    return this->value;
}

void PhysicalProcessMessage::setValue(double value)
{
    this->value = value;
}

double PhysicalProcessMessage::getXCoor() const
{
    return this->xCoor;
}

void PhysicalProcessMessage::setXCoor(double xCoor)
{
    this->xCoor = xCoor;
}

double PhysicalProcessMessage::getYCoor() const
{
    return this->yCoor;
}

void PhysicalProcessMessage::setYCoor(double yCoor)
{
    this->yCoor = yCoor;
}

int PhysicalProcessMessage::getSrcID() const
{
    return this->srcID;
}

void PhysicalProcessMessage::setSrcID(int srcID)
{
    this->srcID = srcID;
}

int PhysicalProcessMessage::getSensorIndex() const
{
    return this->sensorIndex;
}

void PhysicalProcessMessage::setSensorIndex(int sensorIndex)
{
    this->sensorIndex = sensorIndex;
}

class PhysicalProcessMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    PhysicalProcessMessageDescriptor();
    virtual ~PhysicalProcessMessageDescriptor();

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

Register_ClassDescriptor(PhysicalProcessMessageDescriptor);

PhysicalProcessMessageDescriptor::PhysicalProcessMessageDescriptor() : omnetpp::cClassDescriptor("PhysicalProcessMessage", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

PhysicalProcessMessageDescriptor::~PhysicalProcessMessageDescriptor()
{
    delete[] propertynames;
}

bool PhysicalProcessMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PhysicalProcessMessage *>(obj)!=nullptr;
}

const char **PhysicalProcessMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *PhysicalProcessMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int PhysicalProcessMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int PhysicalProcessMessageDescriptor::getFieldTypeFlags(int field) const
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

const char *PhysicalProcessMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "value",
        "xCoor",
        "yCoor",
        "srcID",
        "sensorIndex",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int PhysicalProcessMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+0;
    if (fieldName[0]=='x' && strcmp(fieldName, "xCoor")==0) return base+1;
    if (fieldName[0]=='y' && strcmp(fieldName, "yCoor")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcID")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sensorIndex")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *PhysicalProcessMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "double",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **PhysicalProcessMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *PhysicalProcessMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int PhysicalProcessMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    PhysicalProcessMessage *pp = (PhysicalProcessMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string PhysicalProcessMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    PhysicalProcessMessage *pp = (PhysicalProcessMessage *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getValue());
        case 1: return double2string(pp->getXCoor());
        case 2: return double2string(pp->getYCoor());
        case 3: return long2string(pp->getSrcID());
        case 4: return long2string(pp->getSensorIndex());
        default: return "";
    }
}

bool PhysicalProcessMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    PhysicalProcessMessage *pp = (PhysicalProcessMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setValue(string2double(value)); return true;
        case 1: pp->setXCoor(string2double(value)); return true;
        case 2: pp->setYCoor(string2double(value)); return true;
        case 3: pp->setSrcID(string2long(value)); return true;
        case 4: pp->setSensorIndex(string2long(value)); return true;
        default: return false;
    }
}

const char *PhysicalProcessMessageDescriptor::getFieldStructName(int field) const
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

void *PhysicalProcessMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    PhysicalProcessMessage *pp = (PhysicalProcessMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


