//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/application/wiseCameraKCF/WiseCameraKCFMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseCameraKCFMsg_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("WiseKCFCPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("WiseKCFCPacketType"));
    e->insert(KCF_COLLABORATION_DATA1, "KCF_COLLABORATION_DATA1");
    e->insert(KCF_COLLABORATION_DATA2, "KCF_COLLABORATION_DATA2");
    e->insert(KCF_COLLABORATION_END, "KCF_COLLABORATION_END");
);

Register_Class(WiseCameraKCFMsg);

WiseCameraKCFMsg::WiseCameraKCFMsg(const char *name, int kind) : ::WiseApplicationPacket(name,kind)
{
    this->pktType = 0;
    this->trackingCount = 0;
    this->iterationStep = 0;
    this->targetID = 0;
    this->positionX = 0;
    this->positionY = 0;
    this->TypeNeighbour = 0;
    this->Vx = 0;
    this->Vy = 0;
}

WiseCameraKCFMsg::WiseCameraKCFMsg(const WiseCameraKCFMsg& other) : ::WiseApplicationPacket(other)
{
    copy(other);
}

WiseCameraKCFMsg::~WiseCameraKCFMsg()
{
}

WiseCameraKCFMsg& WiseCameraKCFMsg::operator=(const WiseCameraKCFMsg& other)
{
    if (this==&other) return *this;
    ::WiseApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void WiseCameraKCFMsg::copy(const WiseCameraKCFMsg& other)
{
    this->pktType = other.pktType;
    this->trackingCount = other.trackingCount;
    this->iterationStep = other.iterationStep;
    this->targetID = other.targetID;
    this->positionX = other.positionX;
    this->positionY = other.positionY;
    this->TypeNeighbour = other.TypeNeighbour;
    this->Vx = other.Vx;
    this->Vy = other.Vy;
    this->IF_u = other.IF_u;
    this->IF_U = other.IF_U;
}

void WiseCameraKCFMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WiseApplicationPacket::parsimPack(b);
    doParsimPacking(b,this->pktType);
    doParsimPacking(b,this->trackingCount);
    doParsimPacking(b,this->iterationStep);
    doParsimPacking(b,this->targetID);
    doParsimPacking(b,this->positionX);
    doParsimPacking(b,this->positionY);
    doParsimPacking(b,this->TypeNeighbour);
    doParsimPacking(b,this->Vx);
    doParsimPacking(b,this->Vy);
    doParsimPacking(b,this->IF_u);
    doParsimPacking(b,this->IF_U);
}

void WiseCameraKCFMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WiseApplicationPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->pktType);
    doParsimUnpacking(b,this->trackingCount);
    doParsimUnpacking(b,this->iterationStep);
    doParsimUnpacking(b,this->targetID);
    doParsimUnpacking(b,this->positionX);
    doParsimUnpacking(b,this->positionY);
    doParsimUnpacking(b,this->TypeNeighbour);
    doParsimUnpacking(b,this->Vx);
    doParsimUnpacking(b,this->Vy);
    doParsimUnpacking(b,this->IF_u);
    doParsimUnpacking(b,this->IF_U);
}

unsigned int WiseCameraKCFMsg::getPktType() const
{
    return this->pktType;
}

void WiseCameraKCFMsg::setPktType(unsigned int pktType)
{
    this->pktType = pktType;
}

unsigned long WiseCameraKCFMsg::getTrackingCount() const
{
    return this->trackingCount;
}

void WiseCameraKCFMsg::setTrackingCount(unsigned long trackingCount)
{
    this->trackingCount = trackingCount;
}

unsigned long WiseCameraKCFMsg::getIterationStep() const
{
    return this->iterationStep;
}

void WiseCameraKCFMsg::setIterationStep(unsigned long iterationStep)
{
    this->iterationStep = iterationStep;
}

unsigned int WiseCameraKCFMsg::getTargetID() const
{
    return this->targetID;
}

void WiseCameraKCFMsg::setTargetID(unsigned int targetID)
{
    this->targetID = targetID;
}

double WiseCameraKCFMsg::getPositionX() const
{
    return this->positionX;
}

void WiseCameraKCFMsg::setPositionX(double positionX)
{
    this->positionX = positionX;
}

double WiseCameraKCFMsg::getPositionY() const
{
    return this->positionY;
}

void WiseCameraKCFMsg::setPositionY(double positionY)
{
    this->positionY = positionY;
}

unsigned int WiseCameraKCFMsg::getTypeNeighbour() const
{
    return this->TypeNeighbour;
}

void WiseCameraKCFMsg::setTypeNeighbour(unsigned int TypeNeighbour)
{
    this->TypeNeighbour = TypeNeighbour;
}

double WiseCameraKCFMsg::getVx() const
{
    return this->Vx;
}

void WiseCameraKCFMsg::setVx(double Vx)
{
    this->Vx = Vx;
}

double WiseCameraKCFMsg::getVy() const
{
    return this->Vy;
}

void WiseCameraKCFMsg::setVy(double Vy)
{
    this->Vy = Vy;
}

cv::Mat& WiseCameraKCFMsg::getIF_u()
{
    return this->IF_u;
}

void WiseCameraKCFMsg::setIF_u(const cv::Mat& IF_u)
{
    this->IF_u = IF_u;
}

cv::Mat& WiseCameraKCFMsg::getIF_U()
{
    return this->IF_U;
}

void WiseCameraKCFMsg::setIF_U(const cv::Mat& IF_U)
{
    this->IF_U = IF_U;
}

class WiseCameraKCFMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseCameraKCFMsgDescriptor();
    virtual ~WiseCameraKCFMsgDescriptor();

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

Register_ClassDescriptor(WiseCameraKCFMsgDescriptor);

WiseCameraKCFMsgDescriptor::WiseCameraKCFMsgDescriptor() : omnetpp::cClassDescriptor("WiseCameraKCFMsg", "WiseApplicationPacket")
{
    propertynames = nullptr;
}

WiseCameraKCFMsgDescriptor::~WiseCameraKCFMsgDescriptor()
{
    delete[] propertynames;
}

bool WiseCameraKCFMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseCameraKCFMsg *>(obj)!=nullptr;
}

const char **WiseCameraKCFMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseCameraKCFMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseCameraKCFMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int WiseCameraKCFMsgDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *WiseCameraKCFMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pktType",
        "trackingCount",
        "iterationStep",
        "targetID",
        "positionX",
        "positionY",
        "TypeNeighbour",
        "Vx",
        "Vy",
        "IF_u",
        "IF_U",
    };
    return (field>=0 && field<11) ? fieldNames[field] : nullptr;
}

int WiseCameraKCFMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktType")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trackingCount")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "iterationStep")==0) return base+2;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetID")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionX")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "positionY")==0) return base+5;
    if (fieldName[0]=='T' && strcmp(fieldName, "TypeNeighbour")==0) return base+6;
    if (fieldName[0]=='V' && strcmp(fieldName, "Vx")==0) return base+7;
    if (fieldName[0]=='V' && strcmp(fieldName, "Vy")==0) return base+8;
    if (fieldName[0]=='I' && strcmp(fieldName, "IF_u")==0) return base+9;
    if (fieldName[0]=='I' && strcmp(fieldName, "IF_U")==0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseCameraKCFMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned long",
        "unsigned long",
        "unsigned int",
        "double",
        "double",
        "unsigned int",
        "double",
        "double",
        "cv::Mat",
        "cv::Mat",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseCameraKCFMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseCameraKCFMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseCameraKCFMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseCameraKCFMsg *pp = (WiseCameraKCFMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseCameraKCFMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraKCFMsg *pp = (WiseCameraKCFMsg *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPktType());
        case 1: return ulong2string(pp->getTrackingCount());
        case 2: return ulong2string(pp->getIterationStep());
        case 3: return ulong2string(pp->getTargetID());
        case 4: return double2string(pp->getPositionX());
        case 5: return double2string(pp->getPositionY());
        case 6: return ulong2string(pp->getTypeNeighbour());
        case 7: return double2string(pp->getVx());
        case 8: return double2string(pp->getVy());
        case 9: {std::stringstream out; out << pp->getIF_u(); return out.str();}
        case 10: {std::stringstream out; out << pp->getIF_U(); return out.str();}
        default: return "";
    }
}

bool WiseCameraKCFMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseCameraKCFMsg *pp = (WiseCameraKCFMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setPktType(string2ulong(value)); return true;
        case 1: pp->setTrackingCount(string2ulong(value)); return true;
        case 2: pp->setIterationStep(string2ulong(value)); return true;
        case 3: pp->setTargetID(string2ulong(value)); return true;
        case 4: pp->setPositionX(string2double(value)); return true;
        case 5: pp->setPositionY(string2double(value)); return true;
        case 6: pp->setTypeNeighbour(string2ulong(value)); return true;
        case 7: pp->setVx(string2double(value)); return true;
        case 8: pp->setVy(string2double(value)); return true;
        default: return false;
    }
}

const char *WiseCameraKCFMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 9: return omnetpp::opp_typename(typeid(cv::Mat));
        case 10: return omnetpp::opp_typename(typeid(cv::Mat));
        default: return nullptr;
    };
}

void *WiseCameraKCFMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraKCFMsg *pp = (WiseCameraKCFMsg *)object; (void)pp;
    switch (field) {
        case 9: return (void *)(&pp->getIF_u()); break;
        case 10: return (void *)(&pp->getIF_U()); break;
        default: return nullptr;
    }
}


