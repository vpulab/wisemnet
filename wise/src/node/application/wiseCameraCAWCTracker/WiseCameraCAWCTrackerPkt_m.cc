//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/application/wiseCameraCAWCTracker/WiseCameraCAWCTrackerPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseCameraCAWCTrackerPkt_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("WiseCAWCPacketType");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("WiseCAWCPacketType"));
    e->insert(CAWC_UTILITY, "CAWC_UTILITY");
    e->insert(CAWC_NEWMANAGER, "CAWC_NEWMANAGER");
    e->insert(CAWC_NEWMANAGER_ACK, "CAWC_NEWMANAGER_ACK");
    e->insert(CAWC_NEWMANAGER_ACK_SEND, "CAWC_NEWMANAGER_ACK_SEND");
    e->insert(CAWC_NEWMANAGER_SEND, "CAWC_NEWMANAGER_SEND");
    e->insert(CAWC_NEGOTIATION_JOIN, "CAWC_NEGOTIATION_JOIN");
    e->insert(CAWC_NEGOTIATION_REPLY, "CAWC_NEGOTIATION_REPLY");
    e->insert(CAWC_COLLABORATION_REQUEST, "CAWC_COLLABORATION_REQUEST");
    e->insert(CAWC_COLLABORATION_DATA, "CAWC_COLLABORATION_DATA");
    e->insert(CAWC_COLLABORATION_END, "CAWC_COLLABORATION_END");
);

Register_Class(WiseCameraCAWCTrackerPkt);

WiseCameraCAWCTrackerPkt::WiseCameraCAWCTrackerPkt(const char *name, int kind) : ::WiseApplicationPacket(name,kind)
{
    this->pktType = 0;
    this->nodeID = 0;
    this->camID = 0;
    this->frameID = 0;
    this->utility = 0;
    this->priority = 0;
    this->battery_level = 0;
    this->load_level = 0;
    this->newManager = 0;
    this->initialized = false;
    this->reply = false;
}

WiseCameraCAWCTrackerPkt::WiseCameraCAWCTrackerPkt(const WiseCameraCAWCTrackerPkt& other) : ::WiseApplicationPacket(other)
{
    copy(other);
}

WiseCameraCAWCTrackerPkt::~WiseCameraCAWCTrackerPkt()
{
}

WiseCameraCAWCTrackerPkt& WiseCameraCAWCTrackerPkt::operator=(const WiseCameraCAWCTrackerPkt& other)
{
    if (this==&other) return *this;
    ::WiseApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void WiseCameraCAWCTrackerPkt::copy(const WiseCameraCAWCTrackerPkt& other)
{
    this->pktType = other.pktType;
    this->nodeID = other.nodeID;
    this->camID = other.camID;
    this->frameID = other.frameID;
    this->utility = other.utility;
    this->priority = other.priority;
    this->battery_level = other.battery_level;
    this->load_level = other.load_level;
    this->newManager = other.newManager;
    this->x = other.x;
    this->P = other.P;
    this->initialized = other.initialized;
    this->reply = other.reply;
    this->z = other.z;
    this->H = other.H;
    this->Ht = other.Ht;
    this->Rinv = other.Rinv;
}

void WiseCameraCAWCTrackerPkt::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WiseApplicationPacket::parsimPack(b);
    doParsimPacking(b,this->pktType);
    doParsimPacking(b,this->nodeID);
    doParsimPacking(b,this->camID);
    doParsimPacking(b,this->frameID);
    doParsimPacking(b,this->utility);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->battery_level);
    doParsimPacking(b,this->load_level);
    doParsimPacking(b,this->newManager);
    doParsimPacking(b,this->x);
    doParsimPacking(b,this->P);
    doParsimPacking(b,this->initialized);
    doParsimPacking(b,this->reply);
    doParsimPacking(b,this->z);
    doParsimPacking(b,this->H);
    doParsimPacking(b,this->Ht);
    doParsimPacking(b,this->Rinv);
}

void WiseCameraCAWCTrackerPkt::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WiseApplicationPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->pktType);
    doParsimUnpacking(b,this->nodeID);
    doParsimUnpacking(b,this->camID);
    doParsimUnpacking(b,this->frameID);
    doParsimUnpacking(b,this->utility);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->battery_level);
    doParsimUnpacking(b,this->load_level);
    doParsimUnpacking(b,this->newManager);
    doParsimUnpacking(b,this->x);
    doParsimUnpacking(b,this->P);
    doParsimUnpacking(b,this->initialized);
    doParsimUnpacking(b,this->reply);
    doParsimUnpacking(b,this->z);
    doParsimUnpacking(b,this->H);
    doParsimUnpacking(b,this->Ht);
    doParsimUnpacking(b,this->Rinv);
}

unsigned int WiseCameraCAWCTrackerPkt::getPktType() const
{
    return this->pktType;
}

void WiseCameraCAWCTrackerPkt::setPktType(unsigned int pktType)
{
    this->pktType = pktType;
}

int WiseCameraCAWCTrackerPkt::getNodeID() const
{
    return this->nodeID;
}

void WiseCameraCAWCTrackerPkt::setNodeID(int nodeID)
{
    this->nodeID = nodeID;
}

int WiseCameraCAWCTrackerPkt::getCamID() const
{
    return this->camID;
}

void WiseCameraCAWCTrackerPkt::setCamID(int camID)
{
    this->camID = camID;
}

int WiseCameraCAWCTrackerPkt::getFrameID() const
{
    return this->frameID;
}

void WiseCameraCAWCTrackerPkt::setFrameID(int frameID)
{
    this->frameID = frameID;
}

double WiseCameraCAWCTrackerPkt::getUtility() const
{
    return this->utility;
}

void WiseCameraCAWCTrackerPkt::setUtility(double utility)
{
    this->utility = utility;
}

double WiseCameraCAWCTrackerPkt::getPriority() const
{
    return this->priority;
}

void WiseCameraCAWCTrackerPkt::setPriority(double priority)
{
    this->priority = priority;
}

double WiseCameraCAWCTrackerPkt::getBattery_level() const
{
    return this->battery_level;
}

void WiseCameraCAWCTrackerPkt::setBattery_level(double battery_level)
{
    this->battery_level = battery_level;
}

double WiseCameraCAWCTrackerPkt::getLoad_level() const
{
    return this->load_level;
}

void WiseCameraCAWCTrackerPkt::setLoad_level(double load_level)
{
    this->load_level = load_level;
}

int WiseCameraCAWCTrackerPkt::getNewManager() const
{
    return this->newManager;
}

void WiseCameraCAWCTrackerPkt::setNewManager(int newManager)
{
    this->newManager = newManager;
}

cv::Mat& WiseCameraCAWCTrackerPkt::getX()
{
    return this->x;
}

void WiseCameraCAWCTrackerPkt::setX(const cv::Mat& x)
{
    this->x = x;
}

cv::Mat& WiseCameraCAWCTrackerPkt::getP()
{
    return this->P;
}

void WiseCameraCAWCTrackerPkt::setP(const cv::Mat& P)
{
    this->P = P;
}

bool WiseCameraCAWCTrackerPkt::getInitialized() const
{
    return this->initialized;
}

void WiseCameraCAWCTrackerPkt::setInitialized(bool initialized)
{
    this->initialized = initialized;
}

bool WiseCameraCAWCTrackerPkt::getReply() const
{
    return this->reply;
}

void WiseCameraCAWCTrackerPkt::setReply(bool reply)
{
    this->reply = reply;
}

cv::Mat& WiseCameraCAWCTrackerPkt::getZ()
{
    return this->z;
}

void WiseCameraCAWCTrackerPkt::setZ(const cv::Mat& z)
{
    this->z = z;
}

cv::Mat& WiseCameraCAWCTrackerPkt::getH()
{
    return this->H;
}

void WiseCameraCAWCTrackerPkt::setH(const cv::Mat& H)
{
    this->H = H;
}

cv::Mat& WiseCameraCAWCTrackerPkt::getHt()
{
    return this->Ht;
}

void WiseCameraCAWCTrackerPkt::setHt(const cv::Mat& Ht)
{
    this->Ht = Ht;
}

cv::Mat& WiseCameraCAWCTrackerPkt::getRinv()
{
    return this->Rinv;
}

void WiseCameraCAWCTrackerPkt::setRinv(const cv::Mat& Rinv)
{
    this->Rinv = Rinv;
}

class WiseCameraCAWCTrackerPktDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseCameraCAWCTrackerPktDescriptor();
    virtual ~WiseCameraCAWCTrackerPktDescriptor();

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

Register_ClassDescriptor(WiseCameraCAWCTrackerPktDescriptor);

WiseCameraCAWCTrackerPktDescriptor::WiseCameraCAWCTrackerPktDescriptor() : omnetpp::cClassDescriptor("WiseCameraCAWCTrackerPkt", "WiseApplicationPacket")
{
    propertynames = nullptr;
}

WiseCameraCAWCTrackerPktDescriptor::~WiseCameraCAWCTrackerPktDescriptor()
{
    delete[] propertynames;
}

bool WiseCameraCAWCTrackerPktDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseCameraCAWCTrackerPkt *>(obj)!=nullptr;
}

const char **WiseCameraCAWCTrackerPktDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseCameraCAWCTrackerPktDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseCameraCAWCTrackerPktDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 17+basedesc->getFieldCount() : 17;
}

unsigned int WiseCameraCAWCTrackerPktDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<17) ? fieldTypeFlags[field] : 0;
}

const char *WiseCameraCAWCTrackerPktDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "pktType",
        "nodeID",
        "camID",
        "frameID",
        "utility",
        "priority",
        "battery_level",
        "load_level",
        "newManager",
        "x",
        "P",
        "initialized",
        "reply",
        "z",
        "H",
        "Ht",
        "Rinv",
    };
    return (field>=0 && field<17) ? fieldNames[field] : nullptr;
}

int WiseCameraCAWCTrackerPktDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "pktType")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeID")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "camID")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameID")==0) return base+3;
    if (fieldName[0]=='u' && strcmp(fieldName, "utility")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+5;
    if (fieldName[0]=='b' && strcmp(fieldName, "battery_level")==0) return base+6;
    if (fieldName[0]=='l' && strcmp(fieldName, "load_level")==0) return base+7;
    if (fieldName[0]=='n' && strcmp(fieldName, "newManager")==0) return base+8;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+9;
    if (fieldName[0]=='P' && strcmp(fieldName, "P")==0) return base+10;
    if (fieldName[0]=='i' && strcmp(fieldName, "initialized")==0) return base+11;
    if (fieldName[0]=='r' && strcmp(fieldName, "reply")==0) return base+12;
    if (fieldName[0]=='z' && strcmp(fieldName, "z")==0) return base+13;
    if (fieldName[0]=='H' && strcmp(fieldName, "H")==0) return base+14;
    if (fieldName[0]=='H' && strcmp(fieldName, "Ht")==0) return base+15;
    if (fieldName[0]=='R' && strcmp(fieldName, "Rinv")==0) return base+16;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseCameraCAWCTrackerPktDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "int",
        "int",
        "int",
        "double",
        "double",
        "double",
        "double",
        "int",
        "cv::Mat",
        "cv::Mat",
        "bool",
        "bool",
        "cv::Mat",
        "cv::Mat",
        "cv::Mat",
        "cv::Mat",
    };
    return (field>=0 && field<17) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseCameraCAWCTrackerPktDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseCameraCAWCTrackerPktDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseCameraCAWCTrackerPktDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseCameraCAWCTrackerPkt *pp = (WiseCameraCAWCTrackerPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseCameraCAWCTrackerPktDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraCAWCTrackerPkt *pp = (WiseCameraCAWCTrackerPkt *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPktType());
        case 1: return long2string(pp->getNodeID());
        case 2: return long2string(pp->getCamID());
        case 3: return long2string(pp->getFrameID());
        case 4: return double2string(pp->getUtility());
        case 5: return double2string(pp->getPriority());
        case 6: return double2string(pp->getBattery_level());
        case 7: return double2string(pp->getLoad_level());
        case 8: return long2string(pp->getNewManager());
        case 9: {std::stringstream out; out << pp->getX(); return out.str();}
        case 10: {std::stringstream out; out << pp->getP(); return out.str();}
        case 11: return bool2string(pp->getInitialized());
        case 12: return bool2string(pp->getReply());
        case 13: {std::stringstream out; out << pp->getZ(); return out.str();}
        case 14: {std::stringstream out; out << pp->getH(); return out.str();}
        case 15: {std::stringstream out; out << pp->getHt(); return out.str();}
        case 16: {std::stringstream out; out << pp->getRinv(); return out.str();}
        default: return "";
    }
}

bool WiseCameraCAWCTrackerPktDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseCameraCAWCTrackerPkt *pp = (WiseCameraCAWCTrackerPkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setPktType(string2ulong(value)); return true;
        case 1: pp->setNodeID(string2long(value)); return true;
        case 2: pp->setCamID(string2long(value)); return true;
        case 3: pp->setFrameID(string2long(value)); return true;
        case 4: pp->setUtility(string2double(value)); return true;
        case 5: pp->setPriority(string2double(value)); return true;
        case 6: pp->setBattery_level(string2double(value)); return true;
        case 7: pp->setLoad_level(string2double(value)); return true;
        case 8: pp->setNewManager(string2long(value)); return true;
        case 11: pp->setInitialized(string2bool(value)); return true;
        case 12: pp->setReply(string2bool(value)); return true;
        default: return false;
    }
}

const char *WiseCameraCAWCTrackerPktDescriptor::getFieldStructName(int field) const
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
        case 13: return omnetpp::opp_typename(typeid(cv::Mat));
        case 14: return omnetpp::opp_typename(typeid(cv::Mat));
        case 15: return omnetpp::opp_typename(typeid(cv::Mat));
        case 16: return omnetpp::opp_typename(typeid(cv::Mat));
        default: return nullptr;
    };
}

void *WiseCameraCAWCTrackerPktDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraCAWCTrackerPkt *pp = (WiseCameraCAWCTrackerPkt *)object; (void)pp;
    switch (field) {
        case 9: return (void *)(&pp->getX()); break;
        case 10: return (void *)(&pp->getP()); break;
        case 13: return (void *)(&pp->getZ()); break;
        case 14: return (void *)(&pp->getH()); break;
        case 15: return (void *)(&pp->getHt()); break;
        case 16: return (void *)(&pp->getRinv()); break;
        default: return nullptr;
    }
}


