//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/node/sensorManager/wiseCameraManager/wiseCameraHandler/WiseCameraDetectionsMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseCameraDetectionsMessage_m.h"

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

WiseTargetDetection::WiseTargetDetection()
{
    this->target_id = 0;
    this->valid = false;
    this->bb_x_tl = 0;
    this->bb_y_tl = 0;
    this->bb_x_br = 0;
    this->bb_y_br = 0;
    this->ext_bb_x_tl = 0;
    this->ext_bb_y_tl = 0;
    this->ext_bb_x_br = 0;
    this->ext_bb_y_br = 0;
    this->true_bb_x_tl = 0;
    this->true_bb_y_tl = 0;
    this->true_bb_x_br = 0;
    this->true_bb_y_br = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const WiseTargetDetection& a)
{
    doParsimPacking(b,a.target_id);
    doParsimPacking(b,a.valid);
    doParsimPacking(b,a.bb_x_tl);
    doParsimPacking(b,a.bb_y_tl);
    doParsimPacking(b,a.bb_x_br);
    doParsimPacking(b,a.bb_y_br);
    doParsimPacking(b,a.ext_bb_x_tl);
    doParsimPacking(b,a.ext_bb_y_tl);
    doParsimPacking(b,a.ext_bb_x_br);
    doParsimPacking(b,a.ext_bb_y_br);
    doParsimPacking(b,a.true_bb_x_tl);
    doParsimPacking(b,a.true_bb_y_tl);
    doParsimPacking(b,a.true_bb_x_br);
    doParsimPacking(b,a.true_bb_y_br);
}

void __doUnpacking(omnetpp::cCommBuffer *b, WiseTargetDetection& a)
{
    doParsimUnpacking(b,a.target_id);
    doParsimUnpacking(b,a.valid);
    doParsimUnpacking(b,a.bb_x_tl);
    doParsimUnpacking(b,a.bb_y_tl);
    doParsimUnpacking(b,a.bb_x_br);
    doParsimUnpacking(b,a.bb_y_br);
    doParsimUnpacking(b,a.ext_bb_x_tl);
    doParsimUnpacking(b,a.ext_bb_y_tl);
    doParsimUnpacking(b,a.ext_bb_x_br);
    doParsimUnpacking(b,a.ext_bb_y_br);
    doParsimUnpacking(b,a.true_bb_x_tl);
    doParsimUnpacking(b,a.true_bb_y_tl);
    doParsimUnpacking(b,a.true_bb_x_br);
    doParsimUnpacking(b,a.true_bb_y_br);
}

class WiseTargetDetectionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseTargetDetectionDescriptor();
    virtual ~WiseTargetDetectionDescriptor();

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

Register_ClassDescriptor(WiseTargetDetectionDescriptor);

WiseTargetDetectionDescriptor::WiseTargetDetectionDescriptor() : omnetpp::cClassDescriptor("WiseTargetDetection", "")
{
    propertynames = nullptr;
}

WiseTargetDetectionDescriptor::~WiseTargetDetectionDescriptor()
{
    delete[] propertynames;
}

bool WiseTargetDetectionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseTargetDetection *>(obj)!=nullptr;
}

const char **WiseTargetDetectionDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseTargetDetectionDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseTargetDetectionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount() : 14;
}

unsigned int WiseTargetDetectionDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<14) ? fieldTypeFlags[field] : 0;
}

const char *WiseTargetDetectionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "target_id",
        "valid",
        "bb_x_tl",
        "bb_y_tl",
        "bb_x_br",
        "bb_y_br",
        "ext_bb_x_tl",
        "ext_bb_y_tl",
        "ext_bb_x_br",
        "ext_bb_y_br",
        "true_bb_x_tl",
        "true_bb_y_tl",
        "true_bb_x_br",
        "true_bb_y_br",
    };
    return (field>=0 && field<14) ? fieldNames[field] : nullptr;
}

int WiseTargetDetectionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "target_id")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "valid")==0) return base+1;
    if (fieldName[0]=='b' && strcmp(fieldName, "bb_x_tl")==0) return base+2;
    if (fieldName[0]=='b' && strcmp(fieldName, "bb_y_tl")==0) return base+3;
    if (fieldName[0]=='b' && strcmp(fieldName, "bb_x_br")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "bb_y_br")==0) return base+5;
    if (fieldName[0]=='e' && strcmp(fieldName, "ext_bb_x_tl")==0) return base+6;
    if (fieldName[0]=='e' && strcmp(fieldName, "ext_bb_y_tl")==0) return base+7;
    if (fieldName[0]=='e' && strcmp(fieldName, "ext_bb_x_br")==0) return base+8;
    if (fieldName[0]=='e' && strcmp(fieldName, "ext_bb_y_br")==0) return base+9;
    if (fieldName[0]=='t' && strcmp(fieldName, "true_bb_x_tl")==0) return base+10;
    if (fieldName[0]=='t' && strcmp(fieldName, "true_bb_y_tl")==0) return base+11;
    if (fieldName[0]=='t' && strcmp(fieldName, "true_bb_x_br")==0) return base+12;
    if (fieldName[0]=='t' && strcmp(fieldName, "true_bb_y_br")==0) return base+13;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseTargetDetectionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "bool",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "unsigned int",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<14) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseTargetDetectionDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseTargetDetectionDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseTargetDetectionDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseTargetDetection *pp = (WiseTargetDetection *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseTargetDetectionDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseTargetDetection *pp = (WiseTargetDetection *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->target_id);
        case 1: return bool2string(pp->valid);
        case 2: return ulong2string(pp->bb_x_tl);
        case 3: return ulong2string(pp->bb_y_tl);
        case 4: return ulong2string(pp->bb_x_br);
        case 5: return ulong2string(pp->bb_y_br);
        case 6: return double2string(pp->ext_bb_x_tl);
        case 7: return double2string(pp->ext_bb_y_tl);
        case 8: return double2string(pp->ext_bb_x_br);
        case 9: return double2string(pp->ext_bb_y_br);
        case 10: return double2string(pp->true_bb_x_tl);
        case 11: return double2string(pp->true_bb_y_tl);
        case 12: return double2string(pp->true_bb_x_br);
        case 13: return double2string(pp->true_bb_y_br);
        default: return "";
    }
}

bool WiseTargetDetectionDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseTargetDetection *pp = (WiseTargetDetection *)object; (void)pp;
    switch (field) {
        case 0: pp->target_id = string2ulong(value); return true;
        case 1: pp->valid = string2bool(value); return true;
        case 2: pp->bb_x_tl = string2ulong(value); return true;
        case 3: pp->bb_y_tl = string2ulong(value); return true;
        case 4: pp->bb_x_br = string2ulong(value); return true;
        case 5: pp->bb_y_br = string2ulong(value); return true;
        case 6: pp->ext_bb_x_tl = string2double(value); return true;
        case 7: pp->ext_bb_y_tl = string2double(value); return true;
        case 8: pp->ext_bb_x_br = string2double(value); return true;
        case 9: pp->ext_bb_y_br = string2double(value); return true;
        case 10: pp->true_bb_x_tl = string2double(value); return true;
        case 11: pp->true_bb_y_tl = string2double(value); return true;
        case 12: pp->true_bb_x_br = string2double(value); return true;
        case 13: pp->true_bb_y_br = string2double(value); return true;
        default: return false;
    }
}

const char *WiseTargetDetectionDescriptor::getFieldStructName(int field) const
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

void *WiseTargetDetectionDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseTargetDetection *pp = (WiseTargetDetection *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WiseCameraDetectionsMessage);

WiseCameraDetectionsMessage::WiseCameraDetectionsMessage(const char *name, int kind) : ::WiseCameraMessage(name,kind)
{
    detections_arraysize = 0;
    this->detections = 0;
}

WiseCameraDetectionsMessage::WiseCameraDetectionsMessage(const WiseCameraDetectionsMessage& other) : ::WiseCameraMessage(other)
{
    detections_arraysize = 0;
    this->detections = 0;
    copy(other);
}

WiseCameraDetectionsMessage::~WiseCameraDetectionsMessage()
{
    delete [] this->detections;
}

WiseCameraDetectionsMessage& WiseCameraDetectionsMessage::operator=(const WiseCameraDetectionsMessage& other)
{
    if (this==&other) return *this;
    ::WiseCameraMessage::operator=(other);
    copy(other);
    return *this;
}

void WiseCameraDetectionsMessage::copy(const WiseCameraDetectionsMessage& other)
{
    delete [] this->detections;
    this->detections = (other.detections_arraysize==0) ? nullptr : new WiseTargetDetection[other.detections_arraysize];
    detections_arraysize = other.detections_arraysize;
    for (unsigned int i=0; i<detections_arraysize; i++)
        this->detections[i] = other.detections[i];
}

void WiseCameraDetectionsMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WiseCameraMessage::parsimPack(b);
    b->pack(detections_arraysize);
    doParsimArrayPacking(b,this->detections,detections_arraysize);
}

void WiseCameraDetectionsMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WiseCameraMessage::parsimUnpack(b);
    delete [] this->detections;
    b->unpack(detections_arraysize);
    if (detections_arraysize==0) {
        this->detections = 0;
    } else {
        this->detections = new WiseTargetDetection[detections_arraysize];
        doParsimArrayUnpacking(b,this->detections,detections_arraysize);
    }
}

void WiseCameraDetectionsMessage::setDetectionsArraySize(unsigned int size)
{
    WiseTargetDetection *detections2 = (size==0) ? nullptr : new WiseTargetDetection[size];
    unsigned int sz = detections_arraysize < size ? detections_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        detections2[i] = this->detections[i];
    detections_arraysize = size;
    delete [] this->detections;
    this->detections = detections2;
}

unsigned int WiseCameraDetectionsMessage::getDetectionsArraySize() const
{
    return detections_arraysize;
}

WiseTargetDetection& WiseCameraDetectionsMessage::getDetections(unsigned int k)
{
    if (k>=detections_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", detections_arraysize, k);
    return this->detections[k];
}

void WiseCameraDetectionsMessage::setDetections(unsigned int k, const WiseTargetDetection& detections)
{
    if (k>=detections_arraysize) throw omnetpp::cRuntimeError("Array of size %d indexed by %d", detections_arraysize, k);
    this->detections[k] = detections;
}

class WiseCameraDetectionsMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseCameraDetectionsMessageDescriptor();
    virtual ~WiseCameraDetectionsMessageDescriptor();

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

Register_ClassDescriptor(WiseCameraDetectionsMessageDescriptor);

WiseCameraDetectionsMessageDescriptor::WiseCameraDetectionsMessageDescriptor() : omnetpp::cClassDescriptor("WiseCameraDetectionsMessage", "WiseCameraMessage")
{
    propertynames = nullptr;
}

WiseCameraDetectionsMessageDescriptor::~WiseCameraDetectionsMessageDescriptor()
{
    delete[] propertynames;
}

bool WiseCameraDetectionsMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseCameraDetectionsMessage *>(obj)!=nullptr;
}

const char **WiseCameraDetectionsMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseCameraDetectionsMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseCameraDetectionsMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int WiseCameraDetectionsMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *WiseCameraDetectionsMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "detections",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int WiseCameraDetectionsMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "detections")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseCameraDetectionsMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "WiseTargetDetection",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseCameraDetectionsMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseCameraDetectionsMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseCameraDetectionsMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDetectionsMessage *pp = (WiseCameraDetectionsMessage *)object; (void)pp;
    switch (field) {
        case 0: return pp->getDetectionsArraySize();
        default: return 0;
    }
}

std::string WiseCameraDetectionsMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDetectionsMessage *pp = (WiseCameraDetectionsMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDetections(i); return out.str();}
        default: return "";
    }
}

bool WiseCameraDetectionsMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDetectionsMessage *pp = (WiseCameraDetectionsMessage *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *WiseCameraDetectionsMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(WiseTargetDetection));
        default: return nullptr;
    };
}

void *WiseCameraDetectionsMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseCameraDetectionsMessage *pp = (WiseCameraDetectionsMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDetections(i)); break;
        default: return nullptr;
    }
}


