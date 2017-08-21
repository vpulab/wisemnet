//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/routing/multipathRingsRouting/MultipathRingsRoutingPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MultipathRingsRoutingPacket_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("multipathRingsRoutingPacketDef");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("multipathRingsRoutingPacketDef"));
    e->insert(MPRINGS_DATA_PACKET, "MPRINGS_DATA_PACKET");
    e->insert(MPRINGS_TOPOLOGY_SETUP_PACKET, "MPRINGS_TOPOLOGY_SETUP_PACKET");
);

Register_Class(MultipathRingsRoutingPacket);

MultipathRingsRoutingPacket::MultipathRingsRoutingPacket(const char *name, int kind) : ::RoutingPacket(name,kind)
{
    this->multipathRingsRoutingPacketKind = 0;
    this->sinkID = 0;
    this->sequenceNumber = 0;
    this->senderLevel = 0;
}

MultipathRingsRoutingPacket::MultipathRingsRoutingPacket(const MultipathRingsRoutingPacket& other) : ::RoutingPacket(other)
{
    copy(other);
}

MultipathRingsRoutingPacket::~MultipathRingsRoutingPacket()
{
}

MultipathRingsRoutingPacket& MultipathRingsRoutingPacket::operator=(const MultipathRingsRoutingPacket& other)
{
    if (this==&other) return *this;
    ::RoutingPacket::operator=(other);
    copy(other);
    return *this;
}

void MultipathRingsRoutingPacket::copy(const MultipathRingsRoutingPacket& other)
{
    this->multipathRingsRoutingPacketKind = other.multipathRingsRoutingPacketKind;
    this->source = other.source;
    this->destination = other.destination;
    this->sinkID = other.sinkID;
    this->sequenceNumber = other.sequenceNumber;
    this->senderLevel = other.senderLevel;
}

void MultipathRingsRoutingPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::RoutingPacket::parsimPack(b);
    doParsimPacking(b,this->multipathRingsRoutingPacketKind);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->sinkID);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->senderLevel);
}

void MultipathRingsRoutingPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::RoutingPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->multipathRingsRoutingPacketKind);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->sinkID);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->senderLevel);
}

int MultipathRingsRoutingPacket::getMultipathRingsRoutingPacketKind() const
{
    return this->multipathRingsRoutingPacketKind;
}

void MultipathRingsRoutingPacket::setMultipathRingsRoutingPacketKind(int multipathRingsRoutingPacketKind)
{
    this->multipathRingsRoutingPacketKind = multipathRingsRoutingPacketKind;
}

const char * MultipathRingsRoutingPacket::getSource() const
{
    return this->source.c_str();
}

void MultipathRingsRoutingPacket::setSource(const char * source)
{
    this->source = source;
}

const char * MultipathRingsRoutingPacket::getDestination() const
{
    return this->destination.c_str();
}

void MultipathRingsRoutingPacket::setDestination(const char * destination)
{
    this->destination = destination;
}

int MultipathRingsRoutingPacket::getSinkID() const
{
    return this->sinkID;
}

void MultipathRingsRoutingPacket::setSinkID(int sinkID)
{
    this->sinkID = sinkID;
}

int MultipathRingsRoutingPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void MultipathRingsRoutingPacket::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

int MultipathRingsRoutingPacket::getSenderLevel() const
{
    return this->senderLevel;
}

void MultipathRingsRoutingPacket::setSenderLevel(int senderLevel)
{
    this->senderLevel = senderLevel;
}

class MultipathRingsRoutingPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    MultipathRingsRoutingPacketDescriptor();
    virtual ~MultipathRingsRoutingPacketDescriptor();

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

Register_ClassDescriptor(MultipathRingsRoutingPacketDescriptor);

MultipathRingsRoutingPacketDescriptor::MultipathRingsRoutingPacketDescriptor() : omnetpp::cClassDescriptor("MultipathRingsRoutingPacket", "RoutingPacket")
{
    propertynames = nullptr;
}

MultipathRingsRoutingPacketDescriptor::~MultipathRingsRoutingPacketDescriptor()
{
    delete[] propertynames;
}

bool MultipathRingsRoutingPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<MultipathRingsRoutingPacket *>(obj)!=nullptr;
}

const char **MultipathRingsRoutingPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *MultipathRingsRoutingPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int MultipathRingsRoutingPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int MultipathRingsRoutingPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *MultipathRingsRoutingPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "multipathRingsRoutingPacketKind",
        "source",
        "destination",
        "sinkID",
        "sequenceNumber",
        "senderLevel",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int MultipathRingsRoutingPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "multipathRingsRoutingPacketKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sinkID")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderLevel")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *MultipathRingsRoutingPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "string",
        "string",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **MultipathRingsRoutingPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *MultipathRingsRoutingPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "multipathRingsRoutingPacketDef";
            return nullptr;
        default: return nullptr;
    }
}

int MultipathRingsRoutingPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MultipathRingsRoutingPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getMultipathRingsRoutingPacketKind(), "multipathRingsRoutingPacketDef");
        case 1: return oppstring2string(pp->getSource());
        case 2: return oppstring2string(pp->getDestination());
        case 3: return long2string(pp->getSinkID());
        case 4: return long2string(pp->getSequenceNumber());
        case 5: return long2string(pp->getSenderLevel());
        default: return "";
    }
}

bool MultipathRingsRoutingPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setMultipathRingsRoutingPacketKind((multipathRingsRoutingPacketDef)string2enum(value, "multipathRingsRoutingPacketDef")); return true;
        case 1: pp->setSource((value)); return true;
        case 2: pp->setDestination((value)); return true;
        case 3: pp->setSinkID(string2long(value)); return true;
        case 4: pp->setSequenceNumber(string2long(value)); return true;
        case 5: pp->setSenderLevel(string2long(value)); return true;
        default: return false;
    }
}

const char *MultipathRingsRoutingPacketDescriptor::getFieldStructName(int field) const
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

void *MultipathRingsRoutingPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    MultipathRingsRoutingPacket *pp = (MultipathRingsRoutingPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


