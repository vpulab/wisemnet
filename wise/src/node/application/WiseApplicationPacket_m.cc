//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/application/WiseApplicationPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseApplicationPacket_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("WiseApplicationPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("WiseApplicationPacketType"));
    e->insert(WISE_APP_NORMAL, "WISE_APP_NORMAL");
    e->insert(WISE_APP_DIRECT_COMMUNICATION, "WISE_APP_DIRECT_COMMUNICATION");
    e->insert(WISE_APP_NEIGHBOUR_DISCOVER_REQUEST, "WISE_APP_NEIGHBOUR_DISCOVER_REQUEST");
    e->insert(WISE_APP_NEIGHBOUR_DISCOVER_REPLY, "WISE_APP_NEIGHBOUR_DISCOVER_REPLY");
    e->insert(WISE_APP_NEIGHBOUR_DISCOVER_TIMEOUT, "WISE_APP_NEIGHBOUR_DISCOVER_TIMEOUT");
    e->insert(WISE_APP_NEIGHBOUR_DISCOVER_DONE, "WISE_APP_NEIGHBOUR_DISCOVER_DONE");
    e->insert(WISE_APP_OUT_OF_ENERGY, "WISE_APP_OUT_OF_ENERGY");
);

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("WiseNeigborhoodPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("WiseNeigborhoodPacketType"));
    e->insert(WISE_NEIGHBOUR_RESET, "WISE_NEIGHBOUR_RESET");
    e->insert(WISE_NEIGHBOUR_UNKNOWN, "WISE_NEIGHBOUR_UNKNOWN");
    e->insert(WISE_NEIGHBOUR_COM, "WISE_NEIGHBOUR_COM");
    e->insert(WISE_NEIGHBOUR_FOV, "WISE_NEIGHBOUR_FOV");
);

Register_Class(WiseApplicationPacket);

WiseApplicationPacket::WiseApplicationPacket(const char *name, int kind) : ::ApplicationGenericDataPacket(name,kind)
{
    payload_arraysize = 0;
    this->payload = 0;
    this->type = WISE_APP_NORMAL;
    this->TypeNeighbour = WISE_NEIGHBOUR_UNKNOWN;
}

WiseApplicationPacket::WiseApplicationPacket(const WiseApplicationPacket& other) : ::ApplicationGenericDataPacket(other)
{
    payload_arraysize = 0;
    this->payload = 0;
    copy(other);
}

WiseApplicationPacket::~WiseApplicationPacket()
{
    delete [] this->payload;
}

WiseApplicationPacket& WiseApplicationPacket::operator=(const WiseApplicationPacket& other)
{
    if (this==&other) return *this;
    ::ApplicationGenericDataPacket::operator=(other);
    copy(other);
    return *this;
}

void WiseApplicationPacket::copy(const WiseApplicationPacket& other)
{
    delete [] this->payload;
    this->payload = (other.payload_arraysize==0) ? nullptr : new unsigned char[other.payload_arraysize];
    payload_arraysize = other.payload_arraysize;
    for (unsigned int i=0; i<payload_arraysize; i++)
        this->payload[i] = other.payload[i];
    this->type = other.type;
    this->TypeNeighbour = other.TypeNeighbour;
}

void WiseApplicationPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::ApplicationGenericDataPacket::parsimPack(b);
    b->pack(payload_arraysize);
    doParsimArrayPacking(b,this->payload,payload_arraysize);
    doParsimPacking(b,this->type);
    doParsimPacking(b,this->TypeNeighbour);
}

void WiseApplicationPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::ApplicationGenericDataPacket::parsimUnpack(b);
    delete [] this->payload;
    b->unpack(payload_arraysize);
    if (payload_arraysize==0) {
        this->payload = 0;
    } else {
        this->payload = new unsigned char[payload_arraysize];
        doParsimArrayUnpacking(b,this->payload,payload_arraysize);
    }
    doParsimUnpacking(b,this->type);
    doParsimUnpacking(b,this->TypeNeighbour);
}

void WiseApplicationPacket::setPayloadArraySize(unsigned int size)
{
    unsigned char *payload2 = (size==0) ? nullptr : new unsigned char[size];
    unsigned int sz = payload_arraysize < size ? payload_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        payload2[i] = this->payload[i];
    for (unsigned int i=sz; i<size; i++)
        payload2[i] = 0;
    payload_arraysize = size;
    delete [] this->payload;
    this->payload = payload2;
}

unsigned int WiseApplicationPacket::getPayloadArraySize() const
{
    return payload_arraysize;
}

unsigned char WiseApplicationPacket::getPayload(unsigned int k) const
{
    if (k>=payload_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", payload_arraysize, k);
    return this->payload[k];
}

void WiseApplicationPacket::setPayload(unsigned int k, unsigned char payload)
{
    if (k>=payload_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", payload_arraysize, k);
    this->payload[k] = payload;
}

unsigned int WiseApplicationPacket::getType() const
{
    return this->type;
}

void WiseApplicationPacket::setType(unsigned int type)
{
    this->type = type;
}

unsigned int WiseApplicationPacket::getTypeNeighbour() const
{
    return this->TypeNeighbour;
}

void WiseApplicationPacket::setTypeNeighbour(unsigned int TypeNeighbour)
{
    this->TypeNeighbour = TypeNeighbour;
}

class WiseApplicationPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseApplicationPacketDescriptor();
    virtual ~WiseApplicationPacketDescriptor();

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

Register_ClassDescriptor(WiseApplicationPacketDescriptor);

WiseApplicationPacketDescriptor::WiseApplicationPacketDescriptor() : omnetpp::cClassDescriptor("WiseApplicationPacket", "ApplicationGenericDataPacket")
{
    propertynames = nullptr;
}

WiseApplicationPacketDescriptor::~WiseApplicationPacketDescriptor()
{
    delete[] propertynames;
}

bool WiseApplicationPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseApplicationPacket *>(obj)!=nullptr;
}

const char **WiseApplicationPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseApplicationPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseApplicationPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int WiseApplicationPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *WiseApplicationPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "payload",
        "type",
        "TypeNeighbour",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int WiseApplicationPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "payload")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+1;
    if (fieldName[0]=='T' && strcmp(fieldName, "TypeNeighbour")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseApplicationPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned int",
        "unsigned int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseApplicationPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseApplicationPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseApplicationPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseApplicationPacket *pp = (WiseApplicationPacket *)object; (void)pp;
    switch (field) {
        case 0: return pp->getPayloadArraySize();
        default: return 0;
    }
}

std::string WiseApplicationPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseApplicationPacket *pp = (WiseApplicationPacket *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPayload(i));
        case 1: return ulong2string(pp->getType());
        case 2: return ulong2string(pp->getTypeNeighbour());
        default: return "";
    }
}

bool WiseApplicationPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseApplicationPacket *pp = (WiseApplicationPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setPayload(i,string2ulong(value)); return true;
        case 1: pp->setType(string2ulong(value)); return true;
        case 2: pp->setTypeNeighbour(string2ulong(value)); return true;
        default: return false;
    }
}

const char *WiseApplicationPacketDescriptor::getFieldStructName(int field) const
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

void *WiseApplicationPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseApplicationPacket *pp = (WiseApplicationPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


