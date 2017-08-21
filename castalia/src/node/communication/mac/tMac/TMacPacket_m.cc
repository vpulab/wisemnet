//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/mac/tMac/TMacPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "TMacPacket_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("TmacPacket_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("TmacPacket_type"));
    e->insert(SYNC_TMAC_PACKET, "SYNC_TMAC_PACKET");
    e->insert(RTS_TMAC_PACKET, "RTS_TMAC_PACKET");
    e->insert(CTS_TMAC_PACKET, "CTS_TMAC_PACKET");
    e->insert(DS_TMAC_PACKET, "DS_TMAC_PACKET");
    e->insert(FRTS_TMAC_PACKET, "FRTS_TMAC_PACKET");
    e->insert(DATA_TMAC_PACKET, "DATA_TMAC_PACKET");
    e->insert(ACK_TMAC_PACKET, "ACK_TMAC_PACKET");
);

Register_Class(TMacPacket);

TMacPacket::TMacPacket(const char *name, int kind) : ::MacPacket(name,kind)
{
    this->type = 0;
    this->source = 0;
    this->destination = 0;
    this->nav = 0;
    this->sequenceNumber = 0;
    this->sync = 0;
    this->syncId = 0;
}

TMacPacket::TMacPacket(const TMacPacket& other) : ::MacPacket(other)
{
    copy(other);
}

TMacPacket::~TMacPacket()
{
}

TMacPacket& TMacPacket::operator=(const TMacPacket& other)
{
    if (this==&other) return *this;
    ::MacPacket::operator=(other);
    copy(other);
    return *this;
}

void TMacPacket::copy(const TMacPacket& other)
{
    this->type = other.type;
    this->source = other.source;
    this->destination = other.destination;
    this->nav = other.nav;
    this->sequenceNumber = other.sequenceNumber;
    this->sync = other.sync;
    this->syncId = other.syncId;
}

void TMacPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::MacPacket::parsimPack(b);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->nav);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->sync);
    doParsimPacking(b,this->syncId);
}

void TMacPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::MacPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->nav);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->sync);
    doParsimUnpacking(b,this->syncId);
}

int TMacPacket::getType() const
{
    return this->type;
}

void TMacPacket::setType(int type)
{
    this->type = type;
}

int TMacPacket::getSource() const
{
    return this->source;
}

void TMacPacket::setSource(int source)
{
    this->source = source;
}

int TMacPacket::getDestination() const
{
    return this->destination;
}

void TMacPacket::setDestination(int destination)
{
    this->destination = destination;
}

::omnetpp::simtime_t TMacPacket::getNav() const
{
    return this->nav;
}

void TMacPacket::setNav(::omnetpp::simtime_t nav)
{
    this->nav = nav;
}

int TMacPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void TMacPacket::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

::omnetpp::simtime_t TMacPacket::getSync() const
{
    return this->sync;
}

void TMacPacket::setSync(::omnetpp::simtime_t sync)
{
    this->sync = sync;
}

int TMacPacket::getSyncId() const
{
    return this->syncId;
}

void TMacPacket::setSyncId(int syncId)
{
    this->syncId = syncId;
}

class TMacPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    TMacPacketDescriptor();
    virtual ~TMacPacketDescriptor();

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

Register_ClassDescriptor(TMacPacketDescriptor);

TMacPacketDescriptor::TMacPacketDescriptor() : omnetpp::cClassDescriptor("TMacPacket", "MacPacket")
{
    propertynames = nullptr;
}

TMacPacketDescriptor::~TMacPacketDescriptor()
{
    delete[] propertynames;
}

bool TMacPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TMacPacket *>(obj)!=nullptr;
}

const char **TMacPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *TMacPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int TMacPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int TMacPacketDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *TMacPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "type",
        "source",
        "destination",
        "nav",
        "sequenceNumber",
        "sync",
        "syncId",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int TMacPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "nav")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sync")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "syncId")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *TMacPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "simtime_t",
        "int",
        "simtime_t",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **TMacPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *TMacPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "TmacPacket_type";
            return nullptr;
        default: return nullptr;
    }
}

int TMacPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    TMacPacket *pp = (TMacPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TMacPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    TMacPacket *pp = (TMacPacket *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getType(), "TmacPacket_type");
        case 1: return long2string(pp->getSource());
        case 2: return long2string(pp->getDestination());
        case 3: return simtime2string(pp->getNav());
        case 4: return long2string(pp->getSequenceNumber());
        case 5: return simtime2string(pp->getSync());
        case 6: return long2string(pp->getSyncId());
        default: return "";
    }
}

bool TMacPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    TMacPacket *pp = (TMacPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setType((TmacPacket_type)string2enum(value, "TmacPacket_type")); return true;
        case 1: pp->setSource(string2long(value)); return true;
        case 2: pp->setDestination(string2long(value)); return true;
        case 3: pp->setNav(string2simtime(value)); return true;
        case 4: pp->setSequenceNumber(string2long(value)); return true;
        case 5: pp->setSync(string2simtime(value)); return true;
        case 6: pp->setSyncId(string2long(value)); return true;
        default: return false;
    }
}

const char *TMacPacketDescriptor::getFieldStructName(int field) const
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

void *TMacPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    TMacPacket *pp = (TMacPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


