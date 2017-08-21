//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/mac/baselineBanMac/BaselineMacPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "BaselineMacPacket_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("SecurityLevel_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("SecurityLevel_type"));
    e->insert(NOT_SECURED, "NOT_SECURED");
    e->insert(AUTHENTICATED_NOT_ENCRYPTED, "AUTHENTICATED_NOT_ENCRYPTED");
    e->insert(AUTHENTICATED_AND_ENCRYPTED, "AUTHENTICATED_AND_ENCRYPTED");
);

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("AcknowledgementPolicy_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("AcknowledgementPolicy_type"));
    e->insert(N_ACK_POLICY, "N_ACK_POLICY");
    e->insert(I_ACK_POLICY, "I_ACK_POLICY");
    e->insert(L_ACK_POLICY, "L_ACK_POLICY");
    e->insert(B_ACK_POLICY, "B_ACK_POLICY");
);

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("Frame_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("Frame_type"));
    e->insert(MANAGEMENT, "MANAGEMENT");
    e->insert(CONTROL, "CONTROL");
    e->insert(DATA, "DATA");
);

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("Frame_subtype");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("Frame_subtype"));
    e->insert(RESERVED, "RESERVED");
    e->insert(BEACON, "BEACON");
    e->insert(ASSOCIATION, "ASSOCIATION");
    e->insert(DISASSOCIATION, "DISASSOCIATION");
    e->insert(PTK, "PTK");
    e->insert(GTK, "GTK");
    e->insert(CONNECTION_REQUEST, "CONNECTION_REQUEST");
    e->insert(CONNECTION_ASSIGNMENT, "CONNECTION_ASSIGNMENT");
    e->insert(DISCONNECTION, "DISCONNECTION");
    e->insert(I_ACK, "I_ACK");
    e->insert(B_ACK, "B_ACK");
    e->insert(I_ACK_POLL, "I_ACK_POLL");
    e->insert(B_ACK_POLL, "B_ACK_POLL");
    e->insert(POLL, "POLL");
    e->insert(T_POLL, "T_POLL");
);

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("statusCode_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("statusCode_type"));
    e->insert(ACCEPTED, "ACCEPTED");
    e->insert(REJ_NO_BANDWIDTH, "REJ_NO_BANDWIDTH");
    e->insert(REJ_NO_NID, "REJ_NO_NID");
    e->insert(REJ_NO_RESOURCES, "REJ_NO_RESOURCES");
    e->insert(REJ_NO_HIGH_SECURITY, "REJ_NO_HIGH_SECURITY");
    e->insert(REJ_NO_LOW_SECURITY, "REJ_NO_LOW_SECURITY");
    e->insert(REJ_NO_REASON, "REJ_NO_REASON");
    e->insert(MODIFIED, "MODIFIED");
);

Register_Class(BaselineMacPacket);

BaselineMacPacket::BaselineMacPacket(const char *name, int kind) : ::MacPacket(name,kind)
{
    this->HID = 0;
    this->NID = 0;
    this->protocolVersion = 0;
    this->securityLevel = 0;
    this->TKindex = 0;
    this->retry = 0;
    this->ackPolicy = 0;
    this->frameType = 0;
    this->frameSubtype = 0;
    this->moreData = 0;
    this->firstFrame = 0;
    this->sequenceNumber = 0;
    this->fragmentNumber = 0;
}

BaselineMacPacket::BaselineMacPacket(const BaselineMacPacket& other) : ::MacPacket(other)
{
    copy(other);
}

BaselineMacPacket::~BaselineMacPacket()
{
}

BaselineMacPacket& BaselineMacPacket::operator=(const BaselineMacPacket& other)
{
    if (this==&other) return *this;
    ::MacPacket::operator=(other);
    copy(other);
    return *this;
}

void BaselineMacPacket::copy(const BaselineMacPacket& other)
{
    this->HID = other.HID;
    this->NID = other.NID;
    this->protocolVersion = other.protocolVersion;
    this->securityLevel = other.securityLevel;
    this->TKindex = other.TKindex;
    this->retry = other.retry;
    this->ackPolicy = other.ackPolicy;
    this->frameType = other.frameType;
    this->frameSubtype = other.frameSubtype;
    this->moreData = other.moreData;
    this->firstFrame = other.firstFrame;
    this->sequenceNumber = other.sequenceNumber;
    this->fragmentNumber = other.fragmentNumber;
}

void BaselineMacPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::MacPacket::parsimPack(b);
    doParsimPacking(b,this->HID);
    doParsimPacking(b,this->NID);
    doParsimPacking(b,this->protocolVersion);
    doParsimPacking(b,this->securityLevel);
    doParsimPacking(b,this->TKindex);
    doParsimPacking(b,this->retry);
    doParsimPacking(b,this->ackPolicy);
    doParsimPacking(b,this->frameType);
    doParsimPacking(b,this->frameSubtype);
    doParsimPacking(b,this->moreData);
    doParsimPacking(b,this->firstFrame);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->fragmentNumber);
}

void BaselineMacPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::MacPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->HID);
    doParsimUnpacking(b,this->NID);
    doParsimUnpacking(b,this->protocolVersion);
    doParsimUnpacking(b,this->securityLevel);
    doParsimUnpacking(b,this->TKindex);
    doParsimUnpacking(b,this->retry);
    doParsimUnpacking(b,this->ackPolicy);
    doParsimUnpacking(b,this->frameType);
    doParsimUnpacking(b,this->frameSubtype);
    doParsimUnpacking(b,this->moreData);
    doParsimUnpacking(b,this->firstFrame);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->fragmentNumber);
}

int BaselineMacPacket::getHID() const
{
    return this->HID;
}

void BaselineMacPacket::setHID(int HID)
{
    this->HID = HID;
}

int BaselineMacPacket::getNID() const
{
    return this->NID;
}

void BaselineMacPacket::setNID(int NID)
{
    this->NID = NID;
}

int BaselineMacPacket::getProtocolVersion() const
{
    return this->protocolVersion;
}

void BaselineMacPacket::setProtocolVersion(int protocolVersion)
{
    this->protocolVersion = protocolVersion;
}

int BaselineMacPacket::getSecurityLevel() const
{
    return this->securityLevel;
}

void BaselineMacPacket::setSecurityLevel(int securityLevel)
{
    this->securityLevel = securityLevel;
}

int BaselineMacPacket::getTKindex() const
{
    return this->TKindex;
}

void BaselineMacPacket::setTKindex(int TKindex)
{
    this->TKindex = TKindex;
}

int BaselineMacPacket::getRetry() const
{
    return this->retry;
}

void BaselineMacPacket::setRetry(int retry)
{
    this->retry = retry;
}

int BaselineMacPacket::getAckPolicy() const
{
    return this->ackPolicy;
}

void BaselineMacPacket::setAckPolicy(int ackPolicy)
{
    this->ackPolicy = ackPolicy;
}

int BaselineMacPacket::getFrameType() const
{
    return this->frameType;
}

void BaselineMacPacket::setFrameType(int frameType)
{
    this->frameType = frameType;
}

int BaselineMacPacket::getFrameSubtype() const
{
    return this->frameSubtype;
}

void BaselineMacPacket::setFrameSubtype(int frameSubtype)
{
    this->frameSubtype = frameSubtype;
}

int BaselineMacPacket::getMoreData() const
{
    return this->moreData;
}

void BaselineMacPacket::setMoreData(int moreData)
{
    this->moreData = moreData;
}

int BaselineMacPacket::getFirstFrame() const
{
    return this->firstFrame;
}

void BaselineMacPacket::setFirstFrame(int firstFrame)
{
    this->firstFrame = firstFrame;
}

int BaselineMacPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void BaselineMacPacket::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

int BaselineMacPacket::getFragmentNumber() const
{
    return this->fragmentNumber;
}

void BaselineMacPacket::setFragmentNumber(int fragmentNumber)
{
    this->fragmentNumber = fragmentNumber;
}

class BaselineMacPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaselineMacPacketDescriptor();
    virtual ~BaselineMacPacketDescriptor();

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

Register_ClassDescriptor(BaselineMacPacketDescriptor);

BaselineMacPacketDescriptor::BaselineMacPacketDescriptor() : omnetpp::cClassDescriptor("BaselineMacPacket", "MacPacket")
{
    propertynames = nullptr;
}

BaselineMacPacketDescriptor::~BaselineMacPacketDescriptor()
{
    delete[] propertynames;
}

bool BaselineMacPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaselineMacPacket *>(obj)!=nullptr;
}

const char **BaselineMacPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaselineMacPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaselineMacPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount() : 13;
}

unsigned int BaselineMacPacketDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *BaselineMacPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "HID",
        "NID",
        "protocolVersion",
        "securityLevel",
        "TKindex",
        "retry",
        "ackPolicy",
        "frameType",
        "frameSubtype",
        "moreData",
        "firstFrame",
        "sequenceNumber",
        "fragmentNumber",
    };
    return (field>=0 && field<13) ? fieldNames[field] : nullptr;
}

int BaselineMacPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='H' && strcmp(fieldName, "HID")==0) return base+0;
    if (fieldName[0]=='N' && strcmp(fieldName, "NID")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "protocolVersion")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "securityLevel")==0) return base+3;
    if (fieldName[0]=='T' && strcmp(fieldName, "TKindex")==0) return base+4;
    if (fieldName[0]=='r' && strcmp(fieldName, "retry")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "ackPolicy")==0) return base+6;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameType")==0) return base+7;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameSubtype")==0) return base+8;
    if (fieldName[0]=='m' && strcmp(fieldName, "moreData")==0) return base+9;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstFrame")==0) return base+10;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+11;
    if (fieldName[0]=='f' && strcmp(fieldName, "fragmentNumber")==0) return base+12;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaselineMacPacketDescriptor::getFieldTypeString(int field) const
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
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : nullptr;
}

const char **BaselineMacPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 3: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case 6: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case 7: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case 8: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BaselineMacPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 3:
            if (!strcmp(propertyname,"enum")) return "SecurityLevel_type";
            return nullptr;
        case 6:
            if (!strcmp(propertyname,"enum")) return "AcknowledgementPolicy_type";
            return nullptr;
        case 7:
            if (!strcmp(propertyname,"enum")) return "Frame_type";
            return nullptr;
        case 8:
            if (!strcmp(propertyname,"enum")) return "Frame_subtype";
            return nullptr;
        default: return nullptr;
    }
}

int BaselineMacPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaselineMacPacket *pp = (BaselineMacPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BaselineMacPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaselineMacPacket *pp = (BaselineMacPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHID());
        case 1: return long2string(pp->getNID());
        case 2: return long2string(pp->getProtocolVersion());
        case 3: return enum2string(pp->getSecurityLevel(), "SecurityLevel_type");
        case 4: return long2string(pp->getTKindex());
        case 5: return long2string(pp->getRetry());
        case 6: return enum2string(pp->getAckPolicy(), "AcknowledgementPolicy_type");
        case 7: return enum2string(pp->getFrameType(), "Frame_type");
        case 8: return enum2string(pp->getFrameSubtype(), "Frame_subtype");
        case 9: return long2string(pp->getMoreData());
        case 10: return long2string(pp->getFirstFrame());
        case 11: return long2string(pp->getSequenceNumber());
        case 12: return long2string(pp->getFragmentNumber());
        default: return "";
    }
}

bool BaselineMacPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaselineMacPacket *pp = (BaselineMacPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setHID(string2long(value)); return true;
        case 1: pp->setNID(string2long(value)); return true;
        case 2: pp->setProtocolVersion(string2long(value)); return true;
        case 3: pp->setSecurityLevel((SecurityLevel_type)string2enum(value, "SecurityLevel_type")); return true;
        case 4: pp->setTKindex(string2long(value)); return true;
        case 5: pp->setRetry(string2long(value)); return true;
        case 6: pp->setAckPolicy((AcknowledgementPolicy_type)string2enum(value, "AcknowledgementPolicy_type")); return true;
        case 7: pp->setFrameType((Frame_type)string2enum(value, "Frame_type")); return true;
        case 8: pp->setFrameSubtype((Frame_subtype)string2enum(value, "Frame_subtype")); return true;
        case 9: pp->setMoreData(string2long(value)); return true;
        case 10: pp->setFirstFrame(string2long(value)); return true;
        case 11: pp->setSequenceNumber(string2long(value)); return true;
        case 12: pp->setFragmentNumber(string2long(value)); return true;
        default: return false;
    }
}

const char *BaselineMacPacketDescriptor::getFieldStructName(int field) const
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

void *BaselineMacPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaselineMacPacket *pp = (BaselineMacPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaselineBeaconPacket);

BaselineBeaconPacket::BaselineBeaconPacket(const char *name, int kind) : ::BaselineMacPacket(name,kind)
{
    this->senderAddress = 0;
    this->beaconShiftingSequenceIndex = 0;
    this->beaconShiftingSequencePhase = 0;
    this->beaconPeriodLength = 0;
    this->allocationSlotLength = 0;
    this->RAP1Length = 0;
    this->RAP2Length = 0;
}

BaselineBeaconPacket::BaselineBeaconPacket(const BaselineBeaconPacket& other) : ::BaselineMacPacket(other)
{
    copy(other);
}

BaselineBeaconPacket::~BaselineBeaconPacket()
{
}

BaselineBeaconPacket& BaselineBeaconPacket::operator=(const BaselineBeaconPacket& other)
{
    if (this==&other) return *this;
    ::BaselineMacPacket::operator=(other);
    copy(other);
    return *this;
}

void BaselineBeaconPacket::copy(const BaselineBeaconPacket& other)
{
    this->senderAddress = other.senderAddress;
    this->beaconShiftingSequenceIndex = other.beaconShiftingSequenceIndex;
    this->beaconShiftingSequencePhase = other.beaconShiftingSequencePhase;
    this->beaconPeriodLength = other.beaconPeriodLength;
    this->allocationSlotLength = other.allocationSlotLength;
    this->RAP1Length = other.RAP1Length;
    this->RAP2Length = other.RAP2Length;
}

void BaselineBeaconPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaselineMacPacket::parsimPack(b);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->beaconShiftingSequenceIndex);
    doParsimPacking(b,this->beaconShiftingSequencePhase);
    doParsimPacking(b,this->beaconPeriodLength);
    doParsimPacking(b,this->allocationSlotLength);
    doParsimPacking(b,this->RAP1Length);
    doParsimPacking(b,this->RAP2Length);
}

void BaselineBeaconPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaselineMacPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->beaconShiftingSequenceIndex);
    doParsimUnpacking(b,this->beaconShiftingSequencePhase);
    doParsimUnpacking(b,this->beaconPeriodLength);
    doParsimUnpacking(b,this->allocationSlotLength);
    doParsimUnpacking(b,this->RAP1Length);
    doParsimUnpacking(b,this->RAP2Length);
}

int BaselineBeaconPacket::getSenderAddress() const
{
    return this->senderAddress;
}

void BaselineBeaconPacket::setSenderAddress(int senderAddress)
{
    this->senderAddress = senderAddress;
}

int BaselineBeaconPacket::getBeaconShiftingSequenceIndex() const
{
    return this->beaconShiftingSequenceIndex;
}

void BaselineBeaconPacket::setBeaconShiftingSequenceIndex(int beaconShiftingSequenceIndex)
{
    this->beaconShiftingSequenceIndex = beaconShiftingSequenceIndex;
}

int BaselineBeaconPacket::getBeaconShiftingSequencePhase() const
{
    return this->beaconShiftingSequencePhase;
}

void BaselineBeaconPacket::setBeaconShiftingSequencePhase(int beaconShiftingSequencePhase)
{
    this->beaconShiftingSequencePhase = beaconShiftingSequencePhase;
}

int BaselineBeaconPacket::getBeaconPeriodLength() const
{
    return this->beaconPeriodLength;
}

void BaselineBeaconPacket::setBeaconPeriodLength(int beaconPeriodLength)
{
    this->beaconPeriodLength = beaconPeriodLength;
}

int BaselineBeaconPacket::getAllocationSlotLength() const
{
    return this->allocationSlotLength;
}

void BaselineBeaconPacket::setAllocationSlotLength(int allocationSlotLength)
{
    this->allocationSlotLength = allocationSlotLength;
}

int BaselineBeaconPacket::getRAP1Length() const
{
    return this->RAP1Length;
}

void BaselineBeaconPacket::setRAP1Length(int RAP1Length)
{
    this->RAP1Length = RAP1Length;
}

int BaselineBeaconPacket::getRAP2Length() const
{
    return this->RAP2Length;
}

void BaselineBeaconPacket::setRAP2Length(int RAP2Length)
{
    this->RAP2Length = RAP2Length;
}

class BaselineBeaconPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaselineBeaconPacketDescriptor();
    virtual ~BaselineBeaconPacketDescriptor();

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

Register_ClassDescriptor(BaselineBeaconPacketDescriptor);

BaselineBeaconPacketDescriptor::BaselineBeaconPacketDescriptor() : omnetpp::cClassDescriptor("BaselineBeaconPacket", "BaselineMacPacket")
{
    propertynames = nullptr;
}

BaselineBeaconPacketDescriptor::~BaselineBeaconPacketDescriptor()
{
    delete[] propertynames;
}

bool BaselineBeaconPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaselineBeaconPacket *>(obj)!=nullptr;
}

const char **BaselineBeaconPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaselineBeaconPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaselineBeaconPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int BaselineBeaconPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *BaselineBeaconPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderAddress",
        "beaconShiftingSequenceIndex",
        "beaconShiftingSequencePhase",
        "beaconPeriodLength",
        "allocationSlotLength",
        "RAP1Length",
        "RAP2Length",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int BaselineBeaconPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconShiftingSequenceIndex")==0) return base+1;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconShiftingSequencePhase")==0) return base+2;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconPeriodLength")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "allocationSlotLength")==0) return base+4;
    if (fieldName[0]=='R' && strcmp(fieldName, "RAP1Length")==0) return base+5;
    if (fieldName[0]=='R' && strcmp(fieldName, "RAP2Length")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaselineBeaconPacketDescriptor::getFieldTypeString(int field) const
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
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **BaselineBeaconPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *BaselineBeaconPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int BaselineBeaconPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaselineBeaconPacket *pp = (BaselineBeaconPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BaselineBeaconPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaselineBeaconPacket *pp = (BaselineBeaconPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSenderAddress());
        case 1: return long2string(pp->getBeaconShiftingSequenceIndex());
        case 2: return long2string(pp->getBeaconShiftingSequencePhase());
        case 3: return long2string(pp->getBeaconPeriodLength());
        case 4: return long2string(pp->getAllocationSlotLength());
        case 5: return long2string(pp->getRAP1Length());
        case 6: return long2string(pp->getRAP2Length());
        default: return "";
    }
}

bool BaselineBeaconPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaselineBeaconPacket *pp = (BaselineBeaconPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setSenderAddress(string2long(value)); return true;
        case 1: pp->setBeaconShiftingSequenceIndex(string2long(value)); return true;
        case 2: pp->setBeaconShiftingSequencePhase(string2long(value)); return true;
        case 3: pp->setBeaconPeriodLength(string2long(value)); return true;
        case 4: pp->setAllocationSlotLength(string2long(value)); return true;
        case 5: pp->setRAP1Length(string2long(value)); return true;
        case 6: pp->setRAP2Length(string2long(value)); return true;
        default: return false;
    }
}

const char *BaselineBeaconPacketDescriptor::getFieldStructName(int field) const
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

void *BaselineBeaconPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaselineBeaconPacket *pp = (BaselineBeaconPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaselineConnectionRequestPacket);

BaselineConnectionRequestPacket::BaselineConnectionRequestPacket(const char *name, int kind) : ::BaselineMacPacket(name,kind)
{
    this->recipientAddress = 0;
    this->senderAddress = 0;
    this->formerHubAddress = 0;
    this->changeIndication = 0;
    this->nextWakeup = 0;
    this->wakeupInterval = 0;
    this->uplinkRequest = 0;
    this->downlinkRequest = 0;
    this->bilinkRequest = 0;
}

BaselineConnectionRequestPacket::BaselineConnectionRequestPacket(const BaselineConnectionRequestPacket& other) : ::BaselineMacPacket(other)
{
    copy(other);
}

BaselineConnectionRequestPacket::~BaselineConnectionRequestPacket()
{
}

BaselineConnectionRequestPacket& BaselineConnectionRequestPacket::operator=(const BaselineConnectionRequestPacket& other)
{
    if (this==&other) return *this;
    ::BaselineMacPacket::operator=(other);
    copy(other);
    return *this;
}

void BaselineConnectionRequestPacket::copy(const BaselineConnectionRequestPacket& other)
{
    this->recipientAddress = other.recipientAddress;
    this->senderAddress = other.senderAddress;
    this->formerHubAddress = other.formerHubAddress;
    this->changeIndication = other.changeIndication;
    this->nextWakeup = other.nextWakeup;
    this->wakeupInterval = other.wakeupInterval;
    this->uplinkRequest = other.uplinkRequest;
    this->downlinkRequest = other.downlinkRequest;
    this->bilinkRequest = other.bilinkRequest;
}

void BaselineConnectionRequestPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaselineMacPacket::parsimPack(b);
    doParsimPacking(b,this->recipientAddress);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->formerHubAddress);
    doParsimPacking(b,this->changeIndication);
    doParsimPacking(b,this->nextWakeup);
    doParsimPacking(b,this->wakeupInterval);
    doParsimPacking(b,this->uplinkRequest);
    doParsimPacking(b,this->downlinkRequest);
    doParsimPacking(b,this->bilinkRequest);
}

void BaselineConnectionRequestPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaselineMacPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->recipientAddress);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->formerHubAddress);
    doParsimUnpacking(b,this->changeIndication);
    doParsimUnpacking(b,this->nextWakeup);
    doParsimUnpacking(b,this->wakeupInterval);
    doParsimUnpacking(b,this->uplinkRequest);
    doParsimUnpacking(b,this->downlinkRequest);
    doParsimUnpacking(b,this->bilinkRequest);
}

int BaselineConnectionRequestPacket::getRecipientAddress() const
{
    return this->recipientAddress;
}

void BaselineConnectionRequestPacket::setRecipientAddress(int recipientAddress)
{
    this->recipientAddress = recipientAddress;
}

int BaselineConnectionRequestPacket::getSenderAddress() const
{
    return this->senderAddress;
}

void BaselineConnectionRequestPacket::setSenderAddress(int senderAddress)
{
    this->senderAddress = senderAddress;
}

int BaselineConnectionRequestPacket::getFormerHubAddress() const
{
    return this->formerHubAddress;
}

void BaselineConnectionRequestPacket::setFormerHubAddress(int formerHubAddress)
{
    this->formerHubAddress = formerHubAddress;
}

int BaselineConnectionRequestPacket::getChangeIndication() const
{
    return this->changeIndication;
}

void BaselineConnectionRequestPacket::setChangeIndication(int changeIndication)
{
    this->changeIndication = changeIndication;
}

int BaselineConnectionRequestPacket::getNextWakeup() const
{
    return this->nextWakeup;
}

void BaselineConnectionRequestPacket::setNextWakeup(int nextWakeup)
{
    this->nextWakeup = nextWakeup;
}

int BaselineConnectionRequestPacket::getWakeupInterval() const
{
    return this->wakeupInterval;
}

void BaselineConnectionRequestPacket::setWakeupInterval(int wakeupInterval)
{
    this->wakeupInterval = wakeupInterval;
}

int BaselineConnectionRequestPacket::getUplinkRequest() const
{
    return this->uplinkRequest;
}

void BaselineConnectionRequestPacket::setUplinkRequest(int uplinkRequest)
{
    this->uplinkRequest = uplinkRequest;
}

int BaselineConnectionRequestPacket::getDownlinkRequest() const
{
    return this->downlinkRequest;
}

void BaselineConnectionRequestPacket::setDownlinkRequest(int downlinkRequest)
{
    this->downlinkRequest = downlinkRequest;
}

int BaselineConnectionRequestPacket::getBilinkRequest() const
{
    return this->bilinkRequest;
}

void BaselineConnectionRequestPacket::setBilinkRequest(int bilinkRequest)
{
    this->bilinkRequest = bilinkRequest;
}

class BaselineConnectionRequestPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaselineConnectionRequestPacketDescriptor();
    virtual ~BaselineConnectionRequestPacketDescriptor();

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

Register_ClassDescriptor(BaselineConnectionRequestPacketDescriptor);

BaselineConnectionRequestPacketDescriptor::BaselineConnectionRequestPacketDescriptor() : omnetpp::cClassDescriptor("BaselineConnectionRequestPacket", "BaselineMacPacket")
{
    propertynames = nullptr;
}

BaselineConnectionRequestPacketDescriptor::~BaselineConnectionRequestPacketDescriptor()
{
    delete[] propertynames;
}

bool BaselineConnectionRequestPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaselineConnectionRequestPacket *>(obj)!=nullptr;
}

const char **BaselineConnectionRequestPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaselineConnectionRequestPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaselineConnectionRequestPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount() : 9;
}

unsigned int BaselineConnectionRequestPacketDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *BaselineConnectionRequestPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "recipientAddress",
        "senderAddress",
        "formerHubAddress",
        "changeIndication",
        "nextWakeup",
        "wakeupInterval",
        "uplinkRequest",
        "downlinkRequest",
        "bilinkRequest",
    };
    return (field>=0 && field<9) ? fieldNames[field] : nullptr;
}

int BaselineConnectionRequestPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "recipientAddress")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "formerHubAddress")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "changeIndication")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextWakeup")==0) return base+4;
    if (fieldName[0]=='w' && strcmp(fieldName, "wakeupInterval")==0) return base+5;
    if (fieldName[0]=='u' && strcmp(fieldName, "uplinkRequest")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "downlinkRequest")==0) return base+7;
    if (fieldName[0]=='b' && strcmp(fieldName, "bilinkRequest")==0) return base+8;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaselineConnectionRequestPacketDescriptor::getFieldTypeString(int field) const
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
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : nullptr;
}

const char **BaselineConnectionRequestPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *BaselineConnectionRequestPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int BaselineConnectionRequestPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionRequestPacket *pp = (BaselineConnectionRequestPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BaselineConnectionRequestPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionRequestPacket *pp = (BaselineConnectionRequestPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRecipientAddress());
        case 1: return long2string(pp->getSenderAddress());
        case 2: return long2string(pp->getFormerHubAddress());
        case 3: return long2string(pp->getChangeIndication());
        case 4: return long2string(pp->getNextWakeup());
        case 5: return long2string(pp->getWakeupInterval());
        case 6: return long2string(pp->getUplinkRequest());
        case 7: return long2string(pp->getDownlinkRequest());
        case 8: return long2string(pp->getBilinkRequest());
        default: return "";
    }
}

bool BaselineConnectionRequestPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionRequestPacket *pp = (BaselineConnectionRequestPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRecipientAddress(string2long(value)); return true;
        case 1: pp->setSenderAddress(string2long(value)); return true;
        case 2: pp->setFormerHubAddress(string2long(value)); return true;
        case 3: pp->setChangeIndication(string2long(value)); return true;
        case 4: pp->setNextWakeup(string2long(value)); return true;
        case 5: pp->setWakeupInterval(string2long(value)); return true;
        case 6: pp->setUplinkRequest(string2long(value)); return true;
        case 7: pp->setDownlinkRequest(string2long(value)); return true;
        case 8: pp->setBilinkRequest(string2long(value)); return true;
        default: return false;
    }
}

const char *BaselineConnectionRequestPacketDescriptor::getFieldStructName(int field) const
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

void *BaselineConnectionRequestPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionRequestPacket *pp = (BaselineConnectionRequestPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaselineConnectionAssignmentPacket);

BaselineConnectionAssignmentPacket::BaselineConnectionAssignmentPacket(const char *name, int kind) : ::BaselineMacPacket(name,kind)
{
    this->recipientAddress = 0;
    this->senderAddress = 0;
    this->channelDwellLength = 0;
    this->channelDwellPhase = 0;
    this->minRAPlength = 0;
    this->statusCode = 0;
    this->assignedNID = 0;
    this->changeIndication = 0;
    this->nextWakeup = 0;
    this->wakeupinterval = 0;
    this->uplinkRequestStart = 0;
    this->uplinkRequestEnd = 0;
    this->downlinkRequestStart = 0;
    this->downlinkRequestEnd = 0;
    this->bilinkRequestStart = 0;
    this->bilinkRequestEnd = 0;
}

BaselineConnectionAssignmentPacket::BaselineConnectionAssignmentPacket(const BaselineConnectionAssignmentPacket& other) : ::BaselineMacPacket(other)
{
    copy(other);
}

BaselineConnectionAssignmentPacket::~BaselineConnectionAssignmentPacket()
{
}

BaselineConnectionAssignmentPacket& BaselineConnectionAssignmentPacket::operator=(const BaselineConnectionAssignmentPacket& other)
{
    if (this==&other) return *this;
    ::BaselineMacPacket::operator=(other);
    copy(other);
    return *this;
}

void BaselineConnectionAssignmentPacket::copy(const BaselineConnectionAssignmentPacket& other)
{
    this->recipientAddress = other.recipientAddress;
    this->senderAddress = other.senderAddress;
    this->channelDwellLength = other.channelDwellLength;
    this->channelDwellPhase = other.channelDwellPhase;
    this->minRAPlength = other.minRAPlength;
    this->statusCode = other.statusCode;
    this->assignedNID = other.assignedNID;
    this->changeIndication = other.changeIndication;
    this->nextWakeup = other.nextWakeup;
    this->wakeupinterval = other.wakeupinterval;
    this->uplinkRequestStart = other.uplinkRequestStart;
    this->uplinkRequestEnd = other.uplinkRequestEnd;
    this->downlinkRequestStart = other.downlinkRequestStart;
    this->downlinkRequestEnd = other.downlinkRequestEnd;
    this->bilinkRequestStart = other.bilinkRequestStart;
    this->bilinkRequestEnd = other.bilinkRequestEnd;
}

void BaselineConnectionAssignmentPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaselineMacPacket::parsimPack(b);
    doParsimPacking(b,this->recipientAddress);
    doParsimPacking(b,this->senderAddress);
    doParsimPacking(b,this->channelDwellLength);
    doParsimPacking(b,this->channelDwellPhase);
    doParsimPacking(b,this->minRAPlength);
    doParsimPacking(b,this->statusCode);
    doParsimPacking(b,this->assignedNID);
    doParsimPacking(b,this->changeIndication);
    doParsimPacking(b,this->nextWakeup);
    doParsimPacking(b,this->wakeupinterval);
    doParsimPacking(b,this->uplinkRequestStart);
    doParsimPacking(b,this->uplinkRequestEnd);
    doParsimPacking(b,this->downlinkRequestStart);
    doParsimPacking(b,this->downlinkRequestEnd);
    doParsimPacking(b,this->bilinkRequestStart);
    doParsimPacking(b,this->bilinkRequestEnd);
}

void BaselineConnectionAssignmentPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaselineMacPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->recipientAddress);
    doParsimUnpacking(b,this->senderAddress);
    doParsimUnpacking(b,this->channelDwellLength);
    doParsimUnpacking(b,this->channelDwellPhase);
    doParsimUnpacking(b,this->minRAPlength);
    doParsimUnpacking(b,this->statusCode);
    doParsimUnpacking(b,this->assignedNID);
    doParsimUnpacking(b,this->changeIndication);
    doParsimUnpacking(b,this->nextWakeup);
    doParsimUnpacking(b,this->wakeupinterval);
    doParsimUnpacking(b,this->uplinkRequestStart);
    doParsimUnpacking(b,this->uplinkRequestEnd);
    doParsimUnpacking(b,this->downlinkRequestStart);
    doParsimUnpacking(b,this->downlinkRequestEnd);
    doParsimUnpacking(b,this->bilinkRequestStart);
    doParsimUnpacking(b,this->bilinkRequestEnd);
}

int BaselineConnectionAssignmentPacket::getRecipientAddress() const
{
    return this->recipientAddress;
}

void BaselineConnectionAssignmentPacket::setRecipientAddress(int recipientAddress)
{
    this->recipientAddress = recipientAddress;
}

int BaselineConnectionAssignmentPacket::getSenderAddress() const
{
    return this->senderAddress;
}

void BaselineConnectionAssignmentPacket::setSenderAddress(int senderAddress)
{
    this->senderAddress = senderAddress;
}

int BaselineConnectionAssignmentPacket::getChannelDwellLength() const
{
    return this->channelDwellLength;
}

void BaselineConnectionAssignmentPacket::setChannelDwellLength(int channelDwellLength)
{
    this->channelDwellLength = channelDwellLength;
}

int BaselineConnectionAssignmentPacket::getChannelDwellPhase() const
{
    return this->channelDwellPhase;
}

void BaselineConnectionAssignmentPacket::setChannelDwellPhase(int channelDwellPhase)
{
    this->channelDwellPhase = channelDwellPhase;
}

int BaselineConnectionAssignmentPacket::getMinRAPlength() const
{
    return this->minRAPlength;
}

void BaselineConnectionAssignmentPacket::setMinRAPlength(int minRAPlength)
{
    this->minRAPlength = minRAPlength;
}

int BaselineConnectionAssignmentPacket::getStatusCode() const
{
    return this->statusCode;
}

void BaselineConnectionAssignmentPacket::setStatusCode(int statusCode)
{
    this->statusCode = statusCode;
}

int BaselineConnectionAssignmentPacket::getAssignedNID() const
{
    return this->assignedNID;
}

void BaselineConnectionAssignmentPacket::setAssignedNID(int assignedNID)
{
    this->assignedNID = assignedNID;
}

int BaselineConnectionAssignmentPacket::getChangeIndication() const
{
    return this->changeIndication;
}

void BaselineConnectionAssignmentPacket::setChangeIndication(int changeIndication)
{
    this->changeIndication = changeIndication;
}

int BaselineConnectionAssignmentPacket::getNextWakeup() const
{
    return this->nextWakeup;
}

void BaselineConnectionAssignmentPacket::setNextWakeup(int nextWakeup)
{
    this->nextWakeup = nextWakeup;
}

int BaselineConnectionAssignmentPacket::getWakeupinterval() const
{
    return this->wakeupinterval;
}

void BaselineConnectionAssignmentPacket::setWakeupinterval(int wakeupinterval)
{
    this->wakeupinterval = wakeupinterval;
}

int BaselineConnectionAssignmentPacket::getUplinkRequestStart() const
{
    return this->uplinkRequestStart;
}

void BaselineConnectionAssignmentPacket::setUplinkRequestStart(int uplinkRequestStart)
{
    this->uplinkRequestStart = uplinkRequestStart;
}

int BaselineConnectionAssignmentPacket::getUplinkRequestEnd() const
{
    return this->uplinkRequestEnd;
}

void BaselineConnectionAssignmentPacket::setUplinkRequestEnd(int uplinkRequestEnd)
{
    this->uplinkRequestEnd = uplinkRequestEnd;
}

int BaselineConnectionAssignmentPacket::getDownlinkRequestStart() const
{
    return this->downlinkRequestStart;
}

void BaselineConnectionAssignmentPacket::setDownlinkRequestStart(int downlinkRequestStart)
{
    this->downlinkRequestStart = downlinkRequestStart;
}

int BaselineConnectionAssignmentPacket::getDownlinkRequestEnd() const
{
    return this->downlinkRequestEnd;
}

void BaselineConnectionAssignmentPacket::setDownlinkRequestEnd(int downlinkRequestEnd)
{
    this->downlinkRequestEnd = downlinkRequestEnd;
}

int BaselineConnectionAssignmentPacket::getBilinkRequestStart() const
{
    return this->bilinkRequestStart;
}

void BaselineConnectionAssignmentPacket::setBilinkRequestStart(int bilinkRequestStart)
{
    this->bilinkRequestStart = bilinkRequestStart;
}

int BaselineConnectionAssignmentPacket::getBilinkRequestEnd() const
{
    return this->bilinkRequestEnd;
}

void BaselineConnectionAssignmentPacket::setBilinkRequestEnd(int bilinkRequestEnd)
{
    this->bilinkRequestEnd = bilinkRequestEnd;
}

class BaselineConnectionAssignmentPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaselineConnectionAssignmentPacketDescriptor();
    virtual ~BaselineConnectionAssignmentPacketDescriptor();

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

Register_ClassDescriptor(BaselineConnectionAssignmentPacketDescriptor);

BaselineConnectionAssignmentPacketDescriptor::BaselineConnectionAssignmentPacketDescriptor() : omnetpp::cClassDescriptor("BaselineConnectionAssignmentPacket", "BaselineMacPacket")
{
    propertynames = nullptr;
}

BaselineConnectionAssignmentPacketDescriptor::~BaselineConnectionAssignmentPacketDescriptor()
{
    delete[] propertynames;
}

bool BaselineConnectionAssignmentPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaselineConnectionAssignmentPacket *>(obj)!=nullptr;
}

const char **BaselineConnectionAssignmentPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaselineConnectionAssignmentPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaselineConnectionAssignmentPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 16+basedesc->getFieldCount() : 16;
}

unsigned int BaselineConnectionAssignmentPacketDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<16) ? fieldTypeFlags[field] : 0;
}

const char *BaselineConnectionAssignmentPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "recipientAddress",
        "senderAddress",
        "channelDwellLength",
        "channelDwellPhase",
        "minRAPlength",
        "statusCode",
        "assignedNID",
        "changeIndication",
        "nextWakeup",
        "wakeupinterval",
        "uplinkRequestStart",
        "uplinkRequestEnd",
        "downlinkRequestStart",
        "downlinkRequestEnd",
        "bilinkRequestStart",
        "bilinkRequestEnd",
    };
    return (field>=0 && field<16) ? fieldNames[field] : nullptr;
}

int BaselineConnectionAssignmentPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "recipientAddress")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderAddress")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelDwellLength")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "channelDwellPhase")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "minRAPlength")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "statusCode")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "assignedNID")==0) return base+6;
    if (fieldName[0]=='c' && strcmp(fieldName, "changeIndication")==0) return base+7;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextWakeup")==0) return base+8;
    if (fieldName[0]=='w' && strcmp(fieldName, "wakeupinterval")==0) return base+9;
    if (fieldName[0]=='u' && strcmp(fieldName, "uplinkRequestStart")==0) return base+10;
    if (fieldName[0]=='u' && strcmp(fieldName, "uplinkRequestEnd")==0) return base+11;
    if (fieldName[0]=='d' && strcmp(fieldName, "downlinkRequestStart")==0) return base+12;
    if (fieldName[0]=='d' && strcmp(fieldName, "downlinkRequestEnd")==0) return base+13;
    if (fieldName[0]=='b' && strcmp(fieldName, "bilinkRequestStart")==0) return base+14;
    if (fieldName[0]=='b' && strcmp(fieldName, "bilinkRequestEnd")==0) return base+15;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaselineConnectionAssignmentPacketDescriptor::getFieldTypeString(int field) const
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
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<16) ? fieldTypeStrings[field] : nullptr;
}

const char **BaselineConnectionAssignmentPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 5: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *BaselineConnectionAssignmentPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 5:
            if (!strcmp(propertyname,"enum")) return "statusCode_type";
            return nullptr;
        default: return nullptr;
    }
}

int BaselineConnectionAssignmentPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionAssignmentPacket *pp = (BaselineConnectionAssignmentPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BaselineConnectionAssignmentPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionAssignmentPacket *pp = (BaselineConnectionAssignmentPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getRecipientAddress());
        case 1: return long2string(pp->getSenderAddress());
        case 2: return long2string(pp->getChannelDwellLength());
        case 3: return long2string(pp->getChannelDwellPhase());
        case 4: return long2string(pp->getMinRAPlength());
        case 5: return enum2string(pp->getStatusCode(), "statusCode_type");
        case 6: return long2string(pp->getAssignedNID());
        case 7: return long2string(pp->getChangeIndication());
        case 8: return long2string(pp->getNextWakeup());
        case 9: return long2string(pp->getWakeupinterval());
        case 10: return long2string(pp->getUplinkRequestStart());
        case 11: return long2string(pp->getUplinkRequestEnd());
        case 12: return long2string(pp->getDownlinkRequestStart());
        case 13: return long2string(pp->getDownlinkRequestEnd());
        case 14: return long2string(pp->getBilinkRequestStart());
        case 15: return long2string(pp->getBilinkRequestEnd());
        default: return "";
    }
}

bool BaselineConnectionAssignmentPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionAssignmentPacket *pp = (BaselineConnectionAssignmentPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setRecipientAddress(string2long(value)); return true;
        case 1: pp->setSenderAddress(string2long(value)); return true;
        case 2: pp->setChannelDwellLength(string2long(value)); return true;
        case 3: pp->setChannelDwellPhase(string2long(value)); return true;
        case 4: pp->setMinRAPlength(string2long(value)); return true;
        case 5: pp->setStatusCode((statusCode_type)string2enum(value, "statusCode_type")); return true;
        case 6: pp->setAssignedNID(string2long(value)); return true;
        case 7: pp->setChangeIndication(string2long(value)); return true;
        case 8: pp->setNextWakeup(string2long(value)); return true;
        case 9: pp->setWakeupinterval(string2long(value)); return true;
        case 10: pp->setUplinkRequestStart(string2long(value)); return true;
        case 11: pp->setUplinkRequestEnd(string2long(value)); return true;
        case 12: pp->setDownlinkRequestStart(string2long(value)); return true;
        case 13: pp->setDownlinkRequestEnd(string2long(value)); return true;
        case 14: pp->setBilinkRequestStart(string2long(value)); return true;
        case 15: pp->setBilinkRequestEnd(string2long(value)); return true;
        default: return false;
    }
}

const char *BaselineConnectionAssignmentPacketDescriptor::getFieldStructName(int field) const
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

void *BaselineConnectionAssignmentPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaselineConnectionAssignmentPacket *pp = (BaselineConnectionAssignmentPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaselineBAckPacket);

BaselineBAckPacket::BaselineBAckPacket(const char *name, int kind) : ::BaselineMacPacket(name,kind)
{
    this->nextBlockSize = 0;
    this->oldestFrameExpected = 0;
    this->frameStatusBitmap = 0;
}

BaselineBAckPacket::BaselineBAckPacket(const BaselineBAckPacket& other) : ::BaselineMacPacket(other)
{
    copy(other);
}

BaselineBAckPacket::~BaselineBAckPacket()
{
}

BaselineBAckPacket& BaselineBAckPacket::operator=(const BaselineBAckPacket& other)
{
    if (this==&other) return *this;
    ::BaselineMacPacket::operator=(other);
    copy(other);
    return *this;
}

void BaselineBAckPacket::copy(const BaselineBAckPacket& other)
{
    this->nextBlockSize = other.nextBlockSize;
    this->oldestFrameExpected = other.oldestFrameExpected;
    this->frameStatusBitmap = other.frameStatusBitmap;
}

void BaselineBAckPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaselineMacPacket::parsimPack(b);
    doParsimPacking(b,this->nextBlockSize);
    doParsimPacking(b,this->oldestFrameExpected);
    doParsimPacking(b,this->frameStatusBitmap);
}

void BaselineBAckPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaselineMacPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->nextBlockSize);
    doParsimUnpacking(b,this->oldestFrameExpected);
    doParsimUnpacking(b,this->frameStatusBitmap);
}

int BaselineBAckPacket::getNextBlockSize() const
{
    return this->nextBlockSize;
}

void BaselineBAckPacket::setNextBlockSize(int nextBlockSize)
{
    this->nextBlockSize = nextBlockSize;
}

int BaselineBAckPacket::getOldestFrameExpected() const
{
    return this->oldestFrameExpected;
}

void BaselineBAckPacket::setOldestFrameExpected(int oldestFrameExpected)
{
    this->oldestFrameExpected = oldestFrameExpected;
}

int BaselineBAckPacket::getFrameStatusBitmap() const
{
    return this->frameStatusBitmap;
}

void BaselineBAckPacket::setFrameStatusBitmap(int frameStatusBitmap)
{
    this->frameStatusBitmap = frameStatusBitmap;
}

class BaselineBAckPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaselineBAckPacketDescriptor();
    virtual ~BaselineBAckPacketDescriptor();

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

Register_ClassDescriptor(BaselineBAckPacketDescriptor);

BaselineBAckPacketDescriptor::BaselineBAckPacketDescriptor() : omnetpp::cClassDescriptor("BaselineBAckPacket", "BaselineMacPacket")
{
    propertynames = nullptr;
}

BaselineBAckPacketDescriptor::~BaselineBAckPacketDescriptor()
{
    delete[] propertynames;
}

bool BaselineBAckPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaselineBAckPacket *>(obj)!=nullptr;
}

const char **BaselineBAckPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaselineBAckPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaselineBAckPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int BaselineBAckPacketDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *BaselineBAckPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "nextBlockSize",
        "oldestFrameExpected",
        "frameStatusBitmap",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int BaselineBAckPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextBlockSize")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "oldestFrameExpected")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameStatusBitmap")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaselineBAckPacketDescriptor::getFieldTypeString(int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **BaselineBAckPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *BaselineBAckPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int BaselineBAckPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaselineBAckPacket *pp = (BaselineBAckPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BaselineBAckPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaselineBAckPacket *pp = (BaselineBAckPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNextBlockSize());
        case 1: return long2string(pp->getOldestFrameExpected());
        case 2: return long2string(pp->getFrameStatusBitmap());
        default: return "";
    }
}

bool BaselineBAckPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaselineBAckPacket *pp = (BaselineBAckPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setNextBlockSize(string2long(value)); return true;
        case 1: pp->setOldestFrameExpected(string2long(value)); return true;
        case 2: pp->setFrameStatusBitmap(string2long(value)); return true;
        default: return false;
    }
}

const char *BaselineBAckPacketDescriptor::getFieldStructName(int field) const
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

void *BaselineBAckPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaselineBAckPacket *pp = (BaselineBAckPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(BaselineTPollPacket);

BaselineTPollPacket::BaselineTPollPacket(const char *name, int kind) : ::BaselineMacPacket(name,kind)
{
    this->currentBeaconPeriod = 0;
    this->currentAllocationSlot = 0;
    this->currentSlotOffset = 0;
    this->beaconPeriodLength = 0;
    this->allocationSlotLength = 0;
}

BaselineTPollPacket::BaselineTPollPacket(const BaselineTPollPacket& other) : ::BaselineMacPacket(other)
{
    copy(other);
}

BaselineTPollPacket::~BaselineTPollPacket()
{
}

BaselineTPollPacket& BaselineTPollPacket::operator=(const BaselineTPollPacket& other)
{
    if (this==&other) return *this;
    ::BaselineMacPacket::operator=(other);
    copy(other);
    return *this;
}

void BaselineTPollPacket::copy(const BaselineTPollPacket& other)
{
    this->currentBeaconPeriod = other.currentBeaconPeriod;
    this->currentAllocationSlot = other.currentAllocationSlot;
    this->currentSlotOffset = other.currentSlotOffset;
    this->beaconPeriodLength = other.beaconPeriodLength;
    this->allocationSlotLength = other.allocationSlotLength;
}

void BaselineTPollPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::BaselineMacPacket::parsimPack(b);
    doParsimPacking(b,this->currentBeaconPeriod);
    doParsimPacking(b,this->currentAllocationSlot);
    doParsimPacking(b,this->currentSlotOffset);
    doParsimPacking(b,this->beaconPeriodLength);
    doParsimPacking(b,this->allocationSlotLength);
}

void BaselineTPollPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::BaselineMacPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->currentBeaconPeriod);
    doParsimUnpacking(b,this->currentAllocationSlot);
    doParsimUnpacking(b,this->currentSlotOffset);
    doParsimUnpacking(b,this->beaconPeriodLength);
    doParsimUnpacking(b,this->allocationSlotLength);
}

int BaselineTPollPacket::getCurrentBeaconPeriod() const
{
    return this->currentBeaconPeriod;
}

void BaselineTPollPacket::setCurrentBeaconPeriod(int currentBeaconPeriod)
{
    this->currentBeaconPeriod = currentBeaconPeriod;
}

int BaselineTPollPacket::getCurrentAllocationSlot() const
{
    return this->currentAllocationSlot;
}

void BaselineTPollPacket::setCurrentAllocationSlot(int currentAllocationSlot)
{
    this->currentAllocationSlot = currentAllocationSlot;
}

int BaselineTPollPacket::getCurrentSlotOffset() const
{
    return this->currentSlotOffset;
}

void BaselineTPollPacket::setCurrentSlotOffset(int currentSlotOffset)
{
    this->currentSlotOffset = currentSlotOffset;
}

int BaselineTPollPacket::getBeaconPeriodLength() const
{
    return this->beaconPeriodLength;
}

void BaselineTPollPacket::setBeaconPeriodLength(int beaconPeriodLength)
{
    this->beaconPeriodLength = beaconPeriodLength;
}

int BaselineTPollPacket::getAllocationSlotLength() const
{
    return this->allocationSlotLength;
}

void BaselineTPollPacket::setAllocationSlotLength(int allocationSlotLength)
{
    this->allocationSlotLength = allocationSlotLength;
}

class BaselineTPollPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    BaselineTPollPacketDescriptor();
    virtual ~BaselineTPollPacketDescriptor();

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

Register_ClassDescriptor(BaselineTPollPacketDescriptor);

BaselineTPollPacketDescriptor::BaselineTPollPacketDescriptor() : omnetpp::cClassDescriptor("BaselineTPollPacket", "BaselineMacPacket")
{
    propertynames = nullptr;
}

BaselineTPollPacketDescriptor::~BaselineTPollPacketDescriptor()
{
    delete[] propertynames;
}

bool BaselineTPollPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BaselineTPollPacket *>(obj)!=nullptr;
}

const char **BaselineTPollPacketDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *BaselineTPollPacketDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int BaselineTPollPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount() : 5;
}

unsigned int BaselineTPollPacketDescriptor::getFieldTypeFlags(int field) const
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

const char *BaselineTPollPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "currentBeaconPeriod",
        "currentAllocationSlot",
        "currentSlotOffset",
        "beaconPeriodLength",
        "allocationSlotLength",
    };
    return (field>=0 && field<5) ? fieldNames[field] : nullptr;
}

int BaselineTPollPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "currentBeaconPeriod")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "currentAllocationSlot")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "currentSlotOffset")==0) return base+2;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconPeriodLength")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "allocationSlotLength")==0) return base+4;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *BaselineTPollPacketDescriptor::getFieldTypeString(int field) const
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
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : nullptr;
}

const char **BaselineTPollPacketDescriptor::getFieldPropertyNames(int field) const
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

const char *BaselineTPollPacketDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int BaselineTPollPacketDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    BaselineTPollPacket *pp = (BaselineTPollPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string BaselineTPollPacketDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    BaselineTPollPacket *pp = (BaselineTPollPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCurrentBeaconPeriod());
        case 1: return long2string(pp->getCurrentAllocationSlot());
        case 2: return long2string(pp->getCurrentSlotOffset());
        case 3: return long2string(pp->getBeaconPeriodLength());
        case 4: return long2string(pp->getAllocationSlotLength());
        default: return "";
    }
}

bool BaselineTPollPacketDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    BaselineTPollPacket *pp = (BaselineTPollPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setCurrentBeaconPeriod(string2long(value)); return true;
        case 1: pp->setCurrentAllocationSlot(string2long(value)); return true;
        case 2: pp->setCurrentSlotOffset(string2long(value)); return true;
        case 3: pp->setBeaconPeriodLength(string2long(value)); return true;
        case 4: pp->setAllocationSlotLength(string2long(value)); return true;
        default: return false;
    }
}

const char *BaselineTPollPacketDescriptor::getFieldStructName(int field) const
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

void *BaselineTPollPacketDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    BaselineTPollPacket *pp = (BaselineTPollPacket *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


