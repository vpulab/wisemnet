//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/world/physicalProcess/wiseVideoFile/WiseVideoFileMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseVideoFileMessage_m.h"

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

Register_Class(WiseVideoFileMessage);

WiseVideoFileMessage::WiseVideoFileMessage(const char *name, int kind) : ::WisePhysicalProcessMessage(name,kind)
{
    this->valid = false;
    this->frameRateSRC = 0;
    this->resize = 0;
    this->curFrame = 0;
}

WiseVideoFileMessage::WiseVideoFileMessage(const WiseVideoFileMessage& other) : ::WisePhysicalProcessMessage(other)
{
    copy(other);
}

WiseVideoFileMessage::~WiseVideoFileMessage()
{
}

WiseVideoFileMessage& WiseVideoFileMessage::operator=(const WiseVideoFileMessage& other)
{
    if (this==&other) return *this;
    ::WisePhysicalProcessMessage::operator=(other);
    copy(other);
    return *this;
}

void WiseVideoFileMessage::copy(const WiseVideoFileMessage& other)
{
    this->valid = other.valid;
    this->fileName = other.fileName;
    this->frameRateSRC = other.frameRateSRC;
    this->resize = other.resize;
    this->curFrame = other.curFrame;
    this->frame = other.frame;
}

void WiseVideoFileMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WisePhysicalProcessMessage::parsimPack(b);
    doParsimPacking(b,this->valid);
    doParsimPacking(b,this->fileName);
    doParsimPacking(b,this->frameRateSRC);
    doParsimPacking(b,this->resize);
    doParsimPacking(b,this->curFrame);
    doParsimPacking(b,this->frame);
}

void WiseVideoFileMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WisePhysicalProcessMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->valid);
    doParsimUnpacking(b,this->fileName);
    doParsimUnpacking(b,this->frameRateSRC);
    doParsimUnpacking(b,this->resize);
    doParsimUnpacking(b,this->curFrame);
    doParsimUnpacking(b,this->frame);
}

bool WiseVideoFileMessage::getValid() const
{
    return this->valid;
}

void WiseVideoFileMessage::setValid(bool valid)
{
    this->valid = valid;
}

const char * WiseVideoFileMessage::getFileName() const
{
    return this->fileName.c_str();
}

void WiseVideoFileMessage::setFileName(const char * fileName)
{
    this->fileName = fileName;
}

double WiseVideoFileMessage::getFrameRateSRC() const
{
    return this->frameRateSRC;
}

void WiseVideoFileMessage::setFrameRateSRC(double frameRateSRC)
{
    this->frameRateSRC = frameRateSRC;
}

double WiseVideoFileMessage::getResize() const
{
    return this->resize;
}

void WiseVideoFileMessage::setResize(double resize)
{
    this->resize = resize;
}

int WiseVideoFileMessage::getCurFrame() const
{
    return this->curFrame;
}

void WiseVideoFileMessage::setCurFrame(int curFrame)
{
    this->curFrame = curFrame;
}

cv::Mat& WiseVideoFileMessage::getFrame()
{
    return this->frame;
}

void WiseVideoFileMessage::setFrame(const cv::Mat& frame)
{
    this->frame = frame;
}

class WiseVideoFileMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseVideoFileMessageDescriptor();
    virtual ~WiseVideoFileMessageDescriptor();

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

Register_ClassDescriptor(WiseVideoFileMessageDescriptor);

WiseVideoFileMessageDescriptor::WiseVideoFileMessageDescriptor() : omnetpp::cClassDescriptor("WiseVideoFileMessage", "WisePhysicalProcessMessage")
{
    propertynames = nullptr;
}

WiseVideoFileMessageDescriptor::~WiseVideoFileMessageDescriptor()
{
    delete[] propertynames;
}

bool WiseVideoFileMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseVideoFileMessage *>(obj)!=nullptr;
}

const char **WiseVideoFileMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseVideoFileMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseVideoFileMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int WiseVideoFileMessageDescriptor::getFieldTypeFlags(int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *WiseVideoFileMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "valid",
        "fileName",
        "frameRateSRC",
        "resize",
        "curFrame",
        "frame",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int WiseVideoFileMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "valid")==0) return base+0;
    if (fieldName[0]=='f' && strcmp(fieldName, "fileName")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameRateSRC")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "resize")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "curFrame")==0) return base+4;
    if (fieldName[0]=='f' && strcmp(fieldName, "frame")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseVideoFileMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "string",
        "double",
        "double",
        "int",
        "cv::Mat",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseVideoFileMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseVideoFileMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseVideoFileMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseVideoFileMessage *pp = (WiseVideoFileMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseVideoFileMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseVideoFileMessage *pp = (WiseVideoFileMessage *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getValid());
        case 1: return oppstring2string(pp->getFileName());
        case 2: return double2string(pp->getFrameRateSRC());
        case 3: return double2string(pp->getResize());
        case 4: return long2string(pp->getCurFrame());
        case 5: {std::stringstream out; out << pp->getFrame(); return out.str();}
        default: return "";
    }
}

bool WiseVideoFileMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseVideoFileMessage *pp = (WiseVideoFileMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setValid(string2bool(value)); return true;
        case 1: pp->setFileName((value)); return true;
        case 2: pp->setFrameRateSRC(string2double(value)); return true;
        case 3: pp->setResize(string2double(value)); return true;
        case 4: pp->setCurFrame(string2long(value)); return true;
        default: return false;
    }
}

const char *WiseVideoFileMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 5: return omnetpp::opp_typename(typeid(cv::Mat));
        default: return nullptr;
    };
}

void *WiseVideoFileMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseVideoFileMessage *pp = (WiseVideoFileMessage *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getFrame()); break;
        default: return nullptr;
    }
}


