//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/application/ApplicationPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ApplicationPacket_m.h"

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

ApplicationInteractionControl_type::ApplicationInteractionControl_type()
{
    this->RSSI = 0;
    this->LQI = 0;
    this->timestamp = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const ApplicationInteractionControl_type& a)
{
    doParsimPacking(b,a.applicationID);
    doParsimPacking(b,a.source);
    doParsimPacking(b,a.destination);
    doParsimPacking(b,a.RSSI);
    doParsimPacking(b,a.LQI);
    doParsimPacking(b,a.timestamp);
}

void __doUnpacking(omnetpp::cCommBuffer *b, ApplicationInteractionControl_type& a)
{
    doParsimUnpacking(b,a.applicationID);
    doParsimUnpacking(b,a.source);
    doParsimUnpacking(b,a.destination);
    doParsimUnpacking(b,a.RSSI);
    doParsimUnpacking(b,a.LQI);
    doParsimUnpacking(b,a.timestamp);
}

class ApplicationInteractionControl_typeDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ApplicationInteractionControl_typeDescriptor();
    virtual ~ApplicationInteractionControl_typeDescriptor();

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

Register_ClassDescriptor(ApplicationInteractionControl_typeDescriptor);

ApplicationInteractionControl_typeDescriptor::ApplicationInteractionControl_typeDescriptor() : omnetpp::cClassDescriptor("ApplicationInteractionControl_type", "")
{
    propertynames = nullptr;
}

ApplicationInteractionControl_typeDescriptor::~ApplicationInteractionControl_typeDescriptor()
{
    delete[] propertynames;
}

bool ApplicationInteractionControl_typeDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ApplicationInteractionControl_type *>(obj)!=nullptr;
}

const char **ApplicationInteractionControl_typeDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ApplicationInteractionControl_typeDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ApplicationInteractionControl_typeDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int ApplicationInteractionControl_typeDescriptor::getFieldTypeFlags(int field) const
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

const char *ApplicationInteractionControl_typeDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "applicationID",
        "source",
        "destination",
        "RSSI",
        "LQI",
        "timestamp",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int ApplicationInteractionControl_typeDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "applicationID")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+2;
    if (fieldName[0]=='R' && strcmp(fieldName, "RSSI")==0) return base+3;
    if (fieldName[0]=='L' && strcmp(fieldName, "LQI")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "timestamp")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ApplicationInteractionControl_typeDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "string",
        "string",
        "double",
        "double",
        "simtime_t",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **ApplicationInteractionControl_typeDescriptor::getFieldPropertyNames(int field) const
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

const char *ApplicationInteractionControl_typeDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ApplicationInteractionControl_typeDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ApplicationInteractionControl_type *pp = (ApplicationInteractionControl_type *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ApplicationInteractionControl_typeDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ApplicationInteractionControl_type *pp = (ApplicationInteractionControl_type *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->applicationID);
        case 1: return oppstring2string(pp->source);
        case 2: return oppstring2string(pp->destination);
        case 3: return double2string(pp->RSSI);
        case 4: return double2string(pp->LQI);
        case 5: return simtime2string(pp->timestamp);
        default: return "";
    }
}

bool ApplicationInteractionControl_typeDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ApplicationInteractionControl_type *pp = (ApplicationInteractionControl_type *)object; (void)pp;
    switch (field) {
        case 0: pp->applicationID = (value); return true;
        case 1: pp->source = (value); return true;
        case 2: pp->destination = (value); return true;
        case 3: pp->RSSI = string2double(value); return true;
        case 4: pp->LQI = string2double(value); return true;
        case 5: pp->timestamp = string2simtime(value); return true;
        default: return false;
    }
}

const char *ApplicationInteractionControl_typeDescriptor::getFieldStructName(int field) const
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

void *ApplicationInteractionControl_typeDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ApplicationInteractionControl_type *pp = (ApplicationInteractionControl_type *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(ApplicationGenericDataPacket);

ApplicationGenericDataPacket::ApplicationGenericDataPacket(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->data = 0;
    this->sequenceNumber = 0;
}

ApplicationGenericDataPacket::ApplicationGenericDataPacket(const ApplicationGenericDataPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

ApplicationGenericDataPacket::~ApplicationGenericDataPacket()
{
}

ApplicationGenericDataPacket& ApplicationGenericDataPacket::operator=(const ApplicationGenericDataPacket& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ApplicationGenericDataPacket::copy(const ApplicationGenericDataPacket& other)
{
    this->applicationInteractionControl = other.applicationInteractionControl;
    this->data = other.data;
    this->sequenceNumber = other.sequenceNumber;
}

void ApplicationGenericDataPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->applicationInteractionControl);
    doParsimPacking(b,this->data);
    doParsimPacking(b,this->sequenceNumber);
}

void ApplicationGenericDataPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->applicationInteractionControl);
    doParsimUnpacking(b,this->data);
    doParsimUnpacking(b,this->sequenceNumber);
}

ApplicationInteractionControl_type& ApplicationGenericDataPacket::getApplicationInteractionControl()
{
    return this->applicationInteractionControl;
}

void ApplicationGenericDataPacket::setApplicationInteractionControl(const ApplicationInteractionControl_type& applicationInteractionControl)
{
    this->applicationInteractionControl = applicationInteractionControl;
}

double ApplicationGenericDataPacket::getData() const
{
    return this->data;
}

void ApplicationGenericDataPacket::setData(double data)
{
    this->data = data;
}

int ApplicationGenericDataPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void ApplicationGenericDataPacket::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

class ApplicationGenericDataPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    ApplicationGenericDataPacketDescriptor();
    virtual ~ApplicationGenericDataPacketDescriptor();

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

Register_ClassDescriptor(ApplicationGenericDataPacketDescriptor);

ApplicationGenericDataPacketDescriptor::ApplicationGenericDataPacketDescriptor() : omnetpp::cClassDescriptor("ApplicationGenericDataPacket", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

ApplicationGenericDataPacketDescriptor::~ApplicationGenericDataPacketDescriptor()
{
    delete[] propertynames;
}

bool ApplicationGenericDataPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ApplicationGenericDataPacket *>(obj)!=nullptr;
}

const char **ApplicationGenericDataPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *ApplicationGenericDataPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int ApplicationGenericDataPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int ApplicationGenericDataPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ApplicationGenericDataPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "applicationInteractionControl",
        "data",
        "sequenceNumber",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int ApplicationGenericDataPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "applicationInteractionControl")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "data")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *ApplicationGenericDataPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "ApplicationInteractionControl_type",
        "double",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **ApplicationGenericDataPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *ApplicationGenericDataPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int ApplicationGenericDataPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    ApplicationGenericDataPacket *pp = (ApplicationGenericDataPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ApplicationGenericDataPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    ApplicationGenericDataPacket *pp = (ApplicationGenericDataPacket *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getApplicationInteractionControl(); return out.str();}
        case 1: return double2string(pp->getData());
        case 2: return long2string(pp->getSequenceNumber());
        default: return "";
    }
}

bool ApplicationGenericDataPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    ApplicationGenericDataPacket *pp = (ApplicationGenericDataPacket *)object; (void)pp;
    switch (field) {
        case 1: pp->setData(string2double(value)); return true;
        case 2: pp->setSequenceNumber(string2long(value)); return true;
        default: return false;
    }
}

const char *ApplicationGenericDataPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(ApplicationInteractionControl_type));
        default: return nullptr;
    };
}

void *ApplicationGenericDataPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    ApplicationGenericDataPacket *pp = (ApplicationGenericDataPacket *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getApplicationInteractionControl()); break;
        default: return nullptr;
    }
}


