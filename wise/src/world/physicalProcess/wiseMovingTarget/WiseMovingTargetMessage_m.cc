//
// Generated file, do not edit! Created by nedtool 5.0 from wise/src/world/physicalProcess/wiseMovingTarget/WiseMovingTargetMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WiseMovingTargetMessage_m.h"

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

WiseTargetBoundingBox::WiseTargetBoundingBox()
{
    this->x_tl = 0;
    this->y_tl = 0;
    this->z_tl = 0;
    this->x_br = 0;
    this->y_br = 0;
    this->z_br = 0;
}

void __doPacking(omnetpp::cCommBuffer *b, const WiseTargetBoundingBox& a)
{
    doParsimPacking(b,a.x_tl);
    doParsimPacking(b,a.y_tl);
    doParsimPacking(b,a.z_tl);
    doParsimPacking(b,a.x_br);
    doParsimPacking(b,a.y_br);
    doParsimPacking(b,a.z_br);
}

void __doUnpacking(omnetpp::cCommBuffer *b, WiseTargetBoundingBox& a)
{
    doParsimUnpacking(b,a.x_tl);
    doParsimUnpacking(b,a.y_tl);
    doParsimUnpacking(b,a.z_tl);
    doParsimUnpacking(b,a.x_br);
    doParsimUnpacking(b,a.y_br);
    doParsimUnpacking(b,a.z_br);
}

class WiseTargetBoundingBoxDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseTargetBoundingBoxDescriptor();
    virtual ~WiseTargetBoundingBoxDescriptor();

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

Register_ClassDescriptor(WiseTargetBoundingBoxDescriptor);

WiseTargetBoundingBoxDescriptor::WiseTargetBoundingBoxDescriptor() : omnetpp::cClassDescriptor("WiseTargetBoundingBox", "")
{
    propertynames = nullptr;
}

WiseTargetBoundingBoxDescriptor::~WiseTargetBoundingBoxDescriptor()
{
    delete[] propertynames;
}

bool WiseTargetBoundingBoxDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseTargetBoundingBox *>(obj)!=nullptr;
}

const char **WiseTargetBoundingBoxDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseTargetBoundingBoxDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseTargetBoundingBoxDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int WiseTargetBoundingBoxDescriptor::getFieldTypeFlags(int field) const
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

const char *WiseTargetBoundingBoxDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "x_tl",
        "y_tl",
        "z_tl",
        "x_br",
        "y_br",
        "z_br",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int WiseTargetBoundingBoxDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='x' && strcmp(fieldName, "x_tl")==0) return base+0;
    if (fieldName[0]=='y' && strcmp(fieldName, "y_tl")==0) return base+1;
    if (fieldName[0]=='z' && strcmp(fieldName, "z_tl")==0) return base+2;
    if (fieldName[0]=='x' && strcmp(fieldName, "x_br")==0) return base+3;
    if (fieldName[0]=='y' && strcmp(fieldName, "y_br")==0) return base+4;
    if (fieldName[0]=='z' && strcmp(fieldName, "z_br")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseTargetBoundingBoxDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "double",
        "double",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseTargetBoundingBoxDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseTargetBoundingBoxDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseTargetBoundingBoxDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseTargetBoundingBox *pp = (WiseTargetBoundingBox *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseTargetBoundingBoxDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseTargetBoundingBox *pp = (WiseTargetBoundingBox *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->x_tl);
        case 1: return double2string(pp->y_tl);
        case 2: return double2string(pp->z_tl);
        case 3: return double2string(pp->x_br);
        case 4: return double2string(pp->y_br);
        case 5: return double2string(pp->z_br);
        default: return "";
    }
}

bool WiseTargetBoundingBoxDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseTargetBoundingBox *pp = (WiseTargetBoundingBox *)object; (void)pp;
    switch (field) {
        case 0: pp->x_tl = string2double(value); return true;
        case 1: pp->y_tl = string2double(value); return true;
        case 2: pp->z_tl = string2double(value); return true;
        case 3: pp->x_br = string2double(value); return true;
        case 4: pp->y_br = string2double(value); return true;
        case 5: pp->z_br = string2double(value); return true;
        default: return false;
    }
}

const char *WiseTargetBoundingBoxDescriptor::getFieldStructName(int field) const
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

void *WiseTargetBoundingBoxDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseTargetBoundingBox *pp = (WiseTargetBoundingBox *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

Register_Class(WiseMovingTargetMessage);

WiseMovingTargetMessage::WiseMovingTargetMessage(const char *name, int kind) : ::WisePhysicalProcessMessage(name,kind)
{
    this->targetID = 0;
    this->visible = true;
}

WiseMovingTargetMessage::WiseMovingTargetMessage(const WiseMovingTargetMessage& other) : ::WisePhysicalProcessMessage(other)
{
    copy(other);
}

WiseMovingTargetMessage::~WiseMovingTargetMessage()
{
}

WiseMovingTargetMessage& WiseMovingTargetMessage::operator=(const WiseMovingTargetMessage& other)
{
    if (this==&other) return *this;
    ::WisePhysicalProcessMessage::operator=(other);
    copy(other);
    return *this;
}

void WiseMovingTargetMessage::copy(const WiseMovingTargetMessage& other)
{
    this->boundingBox = other.boundingBox;
    this->targetID = other.targetID;
    this->visible = other.visible;
}

void WiseMovingTargetMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::WisePhysicalProcessMessage::parsimPack(b);
    doParsimPacking(b,this->boundingBox);
    doParsimPacking(b,this->targetID);
    doParsimPacking(b,this->visible);
}

void WiseMovingTargetMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::WisePhysicalProcessMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->boundingBox);
    doParsimUnpacking(b,this->targetID);
    doParsimUnpacking(b,this->visible);
}

WiseTargetBoundingBox& WiseMovingTargetMessage::getBoundingBox()
{
    return this->boundingBox;
}

void WiseMovingTargetMessage::setBoundingBox(const WiseTargetBoundingBox& boundingBox)
{
    this->boundingBox = boundingBox;
}

unsigned int WiseMovingTargetMessage::getTargetID() const
{
    return this->targetID;
}

void WiseMovingTargetMessage::setTargetID(unsigned int targetID)
{
    this->targetID = targetID;
}

bool WiseMovingTargetMessage::getVisible() const
{
    return this->visible;
}

void WiseMovingTargetMessage::setVisible(bool visible)
{
    this->visible = visible;
}

class WiseMovingTargetMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    WiseMovingTargetMessageDescriptor();
    virtual ~WiseMovingTargetMessageDescriptor();

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

Register_ClassDescriptor(WiseMovingTargetMessageDescriptor);

WiseMovingTargetMessageDescriptor::WiseMovingTargetMessageDescriptor() : omnetpp::cClassDescriptor("WiseMovingTargetMessage", "WisePhysicalProcessMessage")
{
    propertynames = nullptr;
}

WiseMovingTargetMessageDescriptor::~WiseMovingTargetMessageDescriptor()
{
    delete[] propertynames;
}

bool WiseMovingTargetMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<WiseMovingTargetMessage *>(obj)!=nullptr;
}

const char **WiseMovingTargetMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *WiseMovingTargetMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int WiseMovingTargetMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount() : 3;
}

unsigned int WiseMovingTargetMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *WiseMovingTargetMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "boundingBox",
        "targetID",
        "visible",
    };
    return (field>=0 && field<3) ? fieldNames[field] : nullptr;
}

int WiseMovingTargetMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "boundingBox")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "targetID")==0) return base+1;
    if (fieldName[0]=='v' && strcmp(fieldName, "visible")==0) return base+2;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *WiseMovingTargetMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "WiseTargetBoundingBox",
        "unsigned int",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : nullptr;
}

const char **WiseMovingTargetMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *WiseMovingTargetMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
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

int WiseMovingTargetMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    WiseMovingTargetMessage *pp = (WiseMovingTargetMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WiseMovingTargetMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    WiseMovingTargetMessage *pp = (WiseMovingTargetMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getBoundingBox(); return out.str();}
        case 1: return ulong2string(pp->getTargetID());
        case 2: return bool2string(pp->getVisible());
        default: return "";
    }
}

bool WiseMovingTargetMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    WiseMovingTargetMessage *pp = (WiseMovingTargetMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setTargetID(string2ulong(value)); return true;
        case 2: pp->setVisible(string2bool(value)); return true;
        default: return false;
    }
}

const char *WiseMovingTargetMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0: return omnetpp::opp_typename(typeid(WiseTargetBoundingBox));
        default: return nullptr;
    };
}

void *WiseMovingTargetMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    WiseMovingTargetMessage *pp = (WiseMovingTargetMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getBoundingBox()); break;
        default: return nullptr;
    }
}


