//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/mac/tMac/TMacControlMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "TMacControlMessage_m.h"

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

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("TmacControlMessage_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("TmacControlMessage_type"));
    e->insert(TMAC_TX_FAILURE, "TMAC_TX_FAILURE");
    e->insert(TMAC_TX_SUCCESS, "TMAC_TX_SUCCESS");
);

Register_Class(TMacControlMessage);

TMacControlMessage::TMacControlMessage(const char *name, int kind) : ::omnetpp::cMessage(name,kind)
{
    this->type = 0;
    take(&(this->macPacket));
    this->maxTxRetries = 0;
    this->txRetries = 0;
}

TMacControlMessage::TMacControlMessage(const TMacControlMessage& other) : ::omnetpp::cMessage(other)
{
    take(&(this->macPacket));
    copy(other);
}

TMacControlMessage::~TMacControlMessage()
{
    drop(&(this->macPacket));
}

TMacControlMessage& TMacControlMessage::operator=(const TMacControlMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TMacControlMessage::copy(const TMacControlMessage& other)
{
    this->type = other.type;
    this->macPacket = other.macPacket;
    this->macPacket.setName(other.macPacket.getName());
    this->maxTxRetries = other.maxTxRetries;
    this->txRetries = other.txRetries;
}

void TMacControlMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->macPacket);
    doParsimPacking(b,this->maxTxRetries);
    doParsimPacking(b,this->txRetries);
}

void TMacControlMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->macPacket);
    doParsimUnpacking(b,this->maxTxRetries);
    doParsimUnpacking(b,this->txRetries);
}

int TMacControlMessage::getType() const
{
    return this->type;
}

void TMacControlMessage::setType(int type)
{
    this->type = type;
}

TMacPacket& TMacControlMessage::getMacPacket()
{
    return this->macPacket;
}

void TMacControlMessage::setMacPacket(const TMacPacket& macPacket)
{
    this->macPacket = macPacket;
}

unsigned int TMacControlMessage::getMaxTxRetries() const
{
    return this->maxTxRetries;
}

void TMacControlMessage::setMaxTxRetries(unsigned int maxTxRetries)
{
    this->maxTxRetries = maxTxRetries;
}

unsigned int TMacControlMessage::getTxRetries() const
{
    return this->txRetries;
}

void TMacControlMessage::setTxRetries(unsigned int txRetries)
{
    this->txRetries = txRetries;
}

class TMacControlMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TMacControlMessageDescriptor();
    virtual ~TMacControlMessageDescriptor();

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

Register_ClassDescriptor(TMacControlMessageDescriptor);

TMacControlMessageDescriptor::TMacControlMessageDescriptor() : omnetpp::cClassDescriptor("TMacControlMessage", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

TMacControlMessageDescriptor::~TMacControlMessageDescriptor()
{
    delete[] propertynames;
}

bool TMacControlMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TMacControlMessage *>(obj)!=nullptr;
}

const char **TMacControlMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TMacControlMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TMacControlMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int TMacControlMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *TMacControlMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "macPacket",
        "maxTxRetries",
        "txRetries",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int TMacControlMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "macPacket")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "maxTxRetries")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "txRetries")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TMacControlMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "TMacPacket",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **TMacControlMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TMacControlMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "TmacControlMessage_type";
            return nullptr;
        default: return nullptr;
    }
}

int TMacControlMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TMacControlMessage *pp = (TMacControlMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TMacControlMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TMacControlMessage *pp = (TMacControlMessage *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getType(), "TmacControlMessage_type");
        case 1: {std::stringstream out; out << pp->getMacPacket(); return out.str();}
        case 2: return ulong2string(pp->getMaxTxRetries());
        case 3: return ulong2string(pp->getTxRetries());
        default: return "";
    }
}

bool TMacControlMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TMacControlMessage *pp = (TMacControlMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setType((TmacControlMessage_type)string2enum(value, "TmacControlMessage_type")); return true;
        case 2: pp->setMaxTxRetries(string2ulong(value)); return true;
        case 3: pp->setTxRetries(string2ulong(value)); return true;
        default: return false;
    }
}

const char *TMacControlMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 1: return omnetpp::opp_typename(typeid(TMacPacket));
        default: return nullptr;
    };
}

void *TMacControlMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TMacControlMessage *pp = (TMacControlMessage *)object; (void)pp;
    switch (field) {
        case 1: return (void *)static_cast<omnetpp::cObject *>(&pp->getMacPacket()); break;
        default: return nullptr;
    }
}


