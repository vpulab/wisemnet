//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/application/wiseCameraDPF/WiseCameraDPFMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseCameraDPFMessage_m.h"

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

WiseCameraDPFMessage_Base::WiseCameraDPFMessage_Base(const char *name, int kind) : ::WiseApplicationPacket(name,kind)
{
    this->targetID = 0;
    this->trackingStep = 0;
    this->aggregationStep = 0;
    this->detectionMiss = false;
    this->firstStepFailed = false;
    this->targetLost = false;
    this->firstNodeSelection = false;
    this->firstNodeSelectionScore = 0;
    this->firstNodeSelectionCompleted = false;
    this->firstStartTime = 0;
    this->veryFirstStartTime = 0;
    this->useGmm = false;
    this->fakeVoidPointer = 0;
}

WiseCameraDPFMessage_Base::WiseCameraDPFMessage_Base(const WiseCameraDPFMessage_Base& other) : ::WiseApplicationPacket(other)
{
    copy(other);
}

WiseCameraDPFMessage_Base::~WiseCameraDPFMessage_Base()
{
}

WiseCameraDPFMessage_Base& WiseCameraDPFMessage_Base::operator=(const WiseCameraDPFMessage_Base& other)
{
    if (this==&other) return *this;
    ::WiseApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void WiseCameraDPFMessage_Base::copy(const WiseCameraDPFMessage_Base& other)
{
    this->targetID = other.targetID;
    this->trackingStep = other.trackingStep;
    this->aggregationStep = other.aggregationStep;
    this->detectionMiss = other.detectionMiss;
    this->firstStepFailed = other.firstStepFailed;
    this->targetLost = other.targetLost;
    this->firstNodeSelection = other.firstNodeSelection;
    this->firstNodeSelectionScore = other.firstNodeSelectionScore;
    this->firstNodeSelectionCompleted = other.firstNodeSelectionCompleted;
    this->firstStartTime = other.firstStartTime;
    this->veryFirstStartTime = other.veryFirstStartTime;
    this->useGmm = other.useGmm;
    this->fakeVoidPointer = other.fakeVoidPointer;
}

void WiseCameraDPFMessage_Base::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WiseApplicationPacket::parsimPack(b);
    doParsimPacking(b,this->targetID);
    doParsimPacking(b,this->trackingStep);
    doParsimPacking(b,this->aggregationStep);
    doParsimPacking(b,this->detectionMiss);
    doParsimPacking(b,this->firstStepFailed);
    doParsimPacking(b,this->targetLost);
    doParsimPacking(b,this->firstNodeSelection);
    doParsimPacking(b,this->firstNodeSelectionScore);
    doParsimPacking(b,this->firstNodeSelectionCompleted);
    doParsimPacking(b,this->firstStartTime);
    doParsimPacking(b,this->veryFirstStartTime);
    doParsimPacking(b,this->useGmm);
    doParsimPacking(b,this->fakeVoidPointer);
    // field gmm is abstract -- please do packing in customized class
}

void WiseCameraDPFMessage_Base::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WiseApplicationPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->targetID);
    doParsimUnpacking(b,this->trackingStep);
    doParsimUnpacking(b,this->aggregationStep);
    doParsimUnpacking(b,this->detectionMiss);
    doParsimUnpacking(b,this->firstStepFailed);
    doParsimUnpacking(b,this->targetLost);
    doParsimUnpacking(b,this->firstNodeSelection);
    doParsimUnpacking(b,this->firstNodeSelectionScore);
    doParsimUnpacking(b,this->firstNodeSelectionCompleted);
    doParsimUnpacking(b,this->firstStartTime);
    doParsimUnpacking(b,this->veryFirstStartTime);
    doParsimUnpacking(b,this->useGmm);
    doParsimUnpacking(b,this->fakeVoidPointer);
    // field gmm is abstract -- please do unpacking in customized class
}

unsigned int WiseCameraDPFMessage_Base::getTargetID() const
{
    return this->targetID;
}

void WiseCameraDPFMessage_Base::setTargetID(unsigned int targetID)
{
    this->targetID = targetID;
}

unsigned long WiseCameraDPFMessage_Base::getTrackingStep() const
{
    return this->trackingStep;
}

void WiseCameraDPFMessage_Base::setTrackingStep(unsigned long trackingStep)
{
    this->trackingStep = trackingStep;
}

unsigned int WiseCameraDPFMessage_Base::getAggregationStep() const
{
    return this->aggregationStep;
}

void WiseCameraDPFMessage_Base::setAggregationStep(unsigned int aggregationStep)
{
    this->aggregationStep = aggregationStep;
}

bool WiseCameraDPFMessage_Base::getDetectionMiss() const
{
    return this->detectionMiss;
}

void WiseCameraDPFMessage_Base::setDetectionMiss(bool detectionMiss)
{
    this->detectionMiss = detectionMiss;
}

bool WiseCameraDPFMessage_Base::getFirstStepFailed() const
{
    return this->firstStepFailed;
}

void WiseCameraDPFMessage_Base::setFirstStepFailed(bool firstStepFailed)
{
    this->firstStepFailed = firstStepFailed;
}

bool WiseCameraDPFMessage_Base::getTargetLost() const
{
    return this->targetLost;
}

void WiseCameraDPFMessage_Base::setTargetLost(bool targetLost)
{
    this->targetLost = targetLost;
}

bool WiseCameraDPFMessage_Base::getFirstNodeSelection() const
{
    return this->firstNodeSelection;
}

void WiseCameraDPFMessage_Base::setFirstNodeSelection(bool firstNodeSelection)
{
    this->firstNodeSelection = firstNodeSelection;
}

double WiseCameraDPFMessage_Base::getFirstNodeSelectionScore() const
{
    return this->firstNodeSelectionScore;
}

void WiseCameraDPFMessage_Base::setFirstNodeSelectionScore(double firstNodeSelectionScore)
{
    this->firstNodeSelectionScore = firstNodeSelectionScore;
}

bool WiseCameraDPFMessage_Base::getFirstNodeSelectionCompleted() const
{
    return this->firstNodeSelectionCompleted;
}

void WiseCameraDPFMessage_Base::setFirstNodeSelectionCompleted(bool firstNodeSelectionCompleted)
{
    this->firstNodeSelectionCompleted = firstNodeSelectionCompleted;
}

double WiseCameraDPFMessage_Base::getFirstStartTime() const
{
    return this->firstStartTime;
}

void WiseCameraDPFMessage_Base::setFirstStartTime(double firstStartTime)
{
    this->firstStartTime = firstStartTime;
}

double WiseCameraDPFMessage_Base::getVeryFirstStartTime() const
{
    return this->veryFirstStartTime;
}

void WiseCameraDPFMessage_Base::setVeryFirstStartTime(double veryFirstStartTime)
{
    this->veryFirstStartTime = veryFirstStartTime;
}

bool WiseCameraDPFMessage_Base::getUseGmm() const
{
    return this->useGmm;
}

void WiseCameraDPFMessage_Base::setUseGmm(bool useGmm)
{
    this->useGmm = useGmm;
}

unsigned long WiseCameraDPFMessage_Base::getFakeVoidPointer() const
{
    return this->fakeVoidPointer;
}

void WiseCameraDPFMessage_Base::setFakeVoidPointer(unsigned long fakeVoidPointer)
{
    this->fakeVoidPointer = fakeVoidPointer;
}

class WiseCameraDPFMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseCameraDPFMessageDescriptor();
    virtual ~WiseCameraDPFMessageDescriptor();

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

Register_ClassDescriptor(WiseCameraDPFMessageDescriptor);

WiseCameraDPFMessageDescriptor::WiseCameraDPFMessageDescriptor() : omnetpp::cClassDescriptor("WiseCameraDPFMessage", "WiseApplicationPacket")
{
    propertynames = nullptr;
}

WiseCameraDPFMessageDescriptor::~WiseCameraDPFMessageDescriptor()
{
    delete[] propertynames;
}

bool WiseCameraDPFMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseCameraDPFMessage_Base *>(obj)!=nullptr;
}

const char **WiseCameraDPFMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = { "customize",  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseCameraDPFMessageDescriptor::getProperty(const char *propertyname) const
{
    if (!strcmp(propertyname,"customize")) return "true";
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseCameraDPFMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount() : 14;
}

unsigned int WiseCameraDPFMessageDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<14) ? fieldTypeFlags[field] : 0;
}

const char *WiseCameraDPFMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "targetID",
        "trackingStep",
        "aggregationStep",
        "detectionMiss",
        "firstStepFailed",
        "targetLost",
        "firstNodeSelection",
        "firstNodeSelectionScore",
        "firstNodeSelectionCompleted",
        "firstStartTime",
        "veryFirstStartTime",
        "useGmm",
        "fakeVoidPointer",
        "gmm",
    };
    return (field>=0 && field<14) ? fieldNames[field] : nullptr;
}

int WiseCameraDPFMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetID")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trackingStep")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "aggregationStep")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "detectionMiss")==0) return base+3;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstStepFailed")==0) return base+4;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetLost")==0) return base+5;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstNodeSelection")==0) return base+6;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstNodeSelectionScore")==0) return base+7;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstNodeSelectionCompleted")==0) return base+8;
    if (fieldName[0]=='f' && strcmp(fieldName, "firstStartTime")==0) return base+9;
    if (fieldName[0]=='v' && strcmp(fieldName, "veryFirstStartTime")==0) return base+10;
    if (fieldName[0]=='u' && strcmp(fieldName, "useGmm")==0) return base+11;
    if (fieldName[0]=='f' && strcmp(fieldName, "fakeVoidPointer")==0) return base+12;
    if (fieldName[0]=='g' && strcmp(fieldName, "gmm")==0) return base+13;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseCameraDPFMessageDescriptor::getFieldTypeString(int field) const
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
        "unsigned int",
        "bool",
        "bool",
        "bool",
        "bool",
        "double",
        "bool",
        "double",
        "double",
        "bool",
        "unsigned long",
        "WiseUtils::Gmm::Component",
    };
    return (field>=0 && field<14) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseCameraDPFMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseCameraDPFMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseCameraDPFMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDPFMessage_Base *pp = (WiseCameraDPFMessage_Base *)object; (void)pp;
    switch (field) {
        case 13: return pp->getGmmArraySize();
        default: return 0;
    }
}

std::string WiseCameraDPFMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDPFMessage_Base *pp = (WiseCameraDPFMessage_Base *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getTargetID());
        case 1: return ulong2string(pp->getTrackingStep());
        case 2: return ulong2string(pp->getAggregationStep());
        case 3: return bool2string(pp->getDetectionMiss());
        case 4: return bool2string(pp->getFirstStepFailed());
        case 5: return bool2string(pp->getTargetLost());
        case 6: return bool2string(pp->getFirstNodeSelection());
        case 7: return double2string(pp->getFirstNodeSelectionScore());
        case 8: return bool2string(pp->getFirstNodeSelectionCompleted());
        case 9: return double2string(pp->getFirstStartTime());
        case 10: return double2string(pp->getVeryFirstStartTime());
        case 11: return bool2string(pp->getUseGmm());
        case 12: return ulong2string(pp->getFakeVoidPointer());
        case 13: {std::stringstream out; out << pp->getGmm(i); return out.str();}
        default: return "";
    }
}

bool WiseCameraDPFMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDPFMessage_Base *pp = (WiseCameraDPFMessage_Base *)object; (void)pp;
    switch (field) {
        case 0: pp->setTargetID(string2ulong(value)); return true;
        case 1: pp->setTrackingStep(string2ulong(value)); return true;
        case 2: pp->setAggregationStep(string2ulong(value)); return true;
        case 3: pp->setDetectionMiss(string2bool(value)); return true;
        case 4: pp->setFirstStepFailed(string2bool(value)); return true;
        case 5: pp->setTargetLost(string2bool(value)); return true;
        case 6: pp->setFirstNodeSelection(string2bool(value)); return true;
        case 7: pp->setFirstNodeSelectionScore(string2double(value)); return true;
        case 8: pp->setFirstNodeSelectionCompleted(string2bool(value)); return true;
        case 9: pp->setFirstStartTime(string2double(value)); return true;
        case 10: pp->setVeryFirstStartTime(string2double(value)); return true;
        case 11: pp->setUseGmm(string2bool(value)); return true;
        case 12: pp->setFakeVoidPointer(string2ulong(value)); return true;
        default: return false;
    }
}

const char *WiseCameraDPFMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 13: return omnetpp::opp_typename(typeid(WiseUtils::Gmm::Component));
        default: return nullptr;
    };
}

void *WiseCameraDPFMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDPFMessage_Base *pp = (WiseCameraDPFMessage_Base *)object; (void)pp;
    switch (field) {
        case 13: return (void *)(&pp->getGmm(i)); break;
        default: return nullptr;
    }
}


