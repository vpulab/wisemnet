//
// Generated file, do not edit! Created by nedtool 5.0 from castalia/src/node/communication/radio/RadioControlMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "RadioControlMessage_m.h"

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
    omnetpp::cEnum *e = omnetpp::cEnum::find("RadioControlMessage_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("RadioControlMessage_type"));
    e->insert(CARRIER_SENSE_INTERRUPT, "CARRIER_SENSE_INTERRUPT");
    e->insert(RADIO_BUFFER_FULL, "RADIO_BUFFER_FULL");
);

Register_Class(RadioControlMessage);

RadioControlMessage::RadioControlMessage(const char *name, int kind) : ::omnetpp::cMessage(name,kind)
{
    this->radioControlMessageKind = 0;
}

RadioControlMessage::RadioControlMessage(const RadioControlMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RadioControlMessage::~RadioControlMessage()
{
}

RadioControlMessage& RadioControlMessage::operator=(const RadioControlMessage& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RadioControlMessage::copy(const RadioControlMessage& other)
{
    this->radioControlMessageKind = other.radioControlMessageKind;
}

void RadioControlMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->radioControlMessageKind);
}

void RadioControlMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->radioControlMessageKind);
}

int RadioControlMessage::getRadioControlMessageKind() const
{
    return this->radioControlMessageKind;
}

void RadioControlMessage::setRadioControlMessageKind(int radioControlMessageKind)
{
    this->radioControlMessageKind = radioControlMessageKind;
}

class RadioControlMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RadioControlMessageDescriptor();
    virtual ~RadioControlMessageDescriptor();

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

Register_ClassDescriptor(RadioControlMessageDescriptor);

RadioControlMessageDescriptor::RadioControlMessageDescriptor() : omnetpp::cClassDescriptor("RadioControlMessage", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

RadioControlMessageDescriptor::~RadioControlMessageDescriptor()
{
    delete[] propertynames;
}

bool RadioControlMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RadioControlMessage *>(obj)!=nullptr;
}

const char **RadioControlMessageDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RadioControlMessageDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RadioControlMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount() : 1;
}

unsigned int RadioControlMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *RadioControlMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "radioControlMessageKind",
    };
    return (field>=0 && field<1) ? fieldNames[field] : nullptr;
}

int RadioControlMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "radioControlMessageKind")==0) return base+0;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RadioControlMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : nullptr;
}

const char **RadioControlMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *RadioControlMessageDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "RadioControlMessage_type";
            return nullptr;
        default: return nullptr;
    }
}

int RadioControlMessageDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RadioControlMessage *pp = (RadioControlMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RadioControlMessageDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RadioControlMessage *pp = (RadioControlMessage *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getRadioControlMessageKind(), "RadioControlMessage_type");
        default: return "";
    }
}

bool RadioControlMessageDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RadioControlMessage *pp = (RadioControlMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setRadioControlMessageKind((RadioControlMessage_type)string2enum(value, "RadioControlMessage_type")); return true;
        default: return false;
    }
}

const char *RadioControlMessageDescriptor::getFieldStructName(int field) const
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

void *RadioControlMessageDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RadioControlMessage *pp = (RadioControlMessage *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("BasicState_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("BasicState_type"));
    e->insert(RX, "RX");
    e->insert(TX, "TX");
    e->insert(SLEEP, "SLEEP");
);

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("RadioControlCommand_type");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("RadioControlCommand_type"));
    e->insert(SET_STATE, "SET_STATE");
    e->insert(SET_MODE, "SET_MODE");
    e->insert(SET_TX_OUTPUT, "SET_TX_OUTPUT");
    e->insert(SET_SLEEP_LEVEL, "SET_SLEEP_LEVEL");
    e->insert(SET_CARRIER_FREQ, "SET_CARRIER_FREQ");
    e->insert(SET_CCA_THRESHOLD, "SET_CCA_THRESHOLD");
    e->insert(SET_CS_INTERRUPT_ON, "SET_CS_INTERRUPT_ON");
    e->insert(SET_CS_INTERRUPT_OFF, "SET_CS_INTERRUPT_OFF");
    e->insert(SET_ENCODING, "SET_ENCODING");
);

Register_Class(RadioControlCommand);

RadioControlCommand::RadioControlCommand(const char *name, int kind) : ::omnetpp::cMessage(name,kind)
{
    this->radioControlCommandKind = 0;
    this->state = RX;
    this->parameter = 0.0;
    this->name = "";
}

RadioControlCommand::RadioControlCommand(const RadioControlCommand& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RadioControlCommand::~RadioControlCommand()
{
}

RadioControlCommand& RadioControlCommand::operator=(const RadioControlCommand& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RadioControlCommand::copy(const RadioControlCommand& other)
{
    this->radioControlCommandKind = other.radioControlCommandKind;
    this->state = other.state;
    this->parameter = other.parameter;
    this->name = other.name;
}

void RadioControlCommand::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->radioControlCommandKind);
    doParsimPacking(b,this->state);
    doParsimPacking(b,this->parameter);
    doParsimPacking(b,this->name);
}

void RadioControlCommand::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->radioControlCommandKind);
    doParsimUnpacking(b,this->state);
    doParsimUnpacking(b,this->parameter);
    doParsimUnpacking(b,this->name);
}

int RadioControlCommand::getRadioControlCommandKind() const
{
    return this->radioControlCommandKind;
}

void RadioControlCommand::setRadioControlCommandKind(int radioControlCommandKind)
{
    this->radioControlCommandKind = radioControlCommandKind;
}

int RadioControlCommand::getState() const
{
    return this->state;
}

void RadioControlCommand::setState(int state)
{
    this->state = state;
}

double RadioControlCommand::getParameter() const
{
    return this->parameter;
}

void RadioControlCommand::setParameter(double parameter)
{
    this->parameter = parameter;
}

const char * RadioControlCommand::getName() const
{
    return this->name.c_str();
}

void RadioControlCommand::setName(const char * name)
{
    this->name = name;
}

class RadioControlCommandDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    RadioControlCommandDescriptor();
    virtual ~RadioControlCommandDescriptor();

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

Register_ClassDescriptor(RadioControlCommandDescriptor);

RadioControlCommandDescriptor::RadioControlCommandDescriptor() : omnetpp::cClassDescriptor("RadioControlCommand", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

RadioControlCommandDescriptor::~RadioControlCommandDescriptor()
{
    delete[] propertynames;
}

bool RadioControlCommandDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RadioControlCommand *>(obj)!=nullptr;
}

const char **RadioControlCommandDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *RadioControlCommandDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int RadioControlCommandDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount() : 4;
}

unsigned int RadioControlCommandDescriptor::getFieldTypeFlags(int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *RadioControlCommandDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "radioControlCommandKind",
        "state",
        "parameter",
        "name",
    };
    return (field>=0 && field<4) ? fieldNames[field] : nullptr;
}

int RadioControlCommandDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "radioControlCommandKind")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "state")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "parameter")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "name")==0) return base+3;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *RadioControlCommandDescriptor::getFieldTypeString(int field) const
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
        "double",
        "string",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : nullptr;
}

const char **RadioControlCommandDescriptor::getFieldPropertyNames(int field) const
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
        case 1: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RadioControlCommandDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "RadioControlCommand_type";
            return nullptr;
        case 1:
            if (!strcmp(propertyname,"enum")) return "BasicState_type";
            return nullptr;
        default: return nullptr;
    }
}

int RadioControlCommandDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    RadioControlCommand *pp = (RadioControlCommand *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RadioControlCommandDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    RadioControlCommand *pp = (RadioControlCommand *)object; (void)pp;
    switch (field) {
        case 0: return enum2string(pp->getRadioControlCommandKind(), "RadioControlCommand_type");
        case 1: return enum2string(pp->getState(), "BasicState_type");
        case 2: return double2string(pp->getParameter());
        case 3: return oppstring2string(pp->getName());
        default: return "";
    }
}

bool RadioControlCommandDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    RadioControlCommand *pp = (RadioControlCommand *)object; (void)pp;
    switch (field) {
        case 0: pp->setRadioControlCommandKind((RadioControlCommand_type)string2enum(value, "RadioControlCommand_type")); return true;
        case 1: pp->setState((BasicState_type)string2enum(value, "BasicState_type")); return true;
        case 2: pp->setParameter(string2double(value)); return true;
        case 3: pp->setName((value)); return true;
        default: return false;
    }
}

const char *RadioControlCommandDescriptor::getFieldStructName(int field) const
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

void *RadioControlCommandDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    RadioControlCommand *pp = (RadioControlCommand *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


