#ifndef STATIC_INITIALIZE_H
#define STATIC_INITIALIZE_H

//------------------------------------------------------------------------
// This function handles and maintains reference to ordered global
//		initialization functions. These functions are called in
//		priority order when the game starts.
//		See defines below class definition for usage.
// Memory cost is 8 byte virtual pointer per static intializer
//------------------------------------------------------------------------
class CStaticInitializer {
public:
    enum class EPriority {
        FIRST,
        SECOND,
        THIRD,
        NUM,
    };

    CStaticInitializer(EPriority priority);
    virtual ~CStaticInitializer() {}

    virtual void Invoke() {}

    static void InvokeAllInOrder();

private:
    static TArray<CStaticInitializer*> s_pInitializers[];
};

// use the define and then immediately open braces to define
// the function you want
// order between files for functions of same priority is undefined
// order within the same file for functions of same priority is from
// the top of the file to the bottom
// name collisions only happen within the same file
#define STATIC_INTIALIZE(identifier, priority)                                      \
    static void StaticInitializerFunc_##identifier();                               \
    namespace {                                                                     \
    class CStaticInitializer_##identifier : public CStaticInitializer {             \
    public:                                                                         \
        CStaticInitializer_##identifier(EPriority p) : CStaticInitializer(p) {}     \
        void Invoke() override { StaticInitializerFunc_##identifier(); }            \
    };                                                                              \
    }                                                                               \
    static CStaticInitializer_##identifier g_staticInitializer_##identifier(        \
        CStaticInitializer::EPriority::priority);                                   \
    static void StaticInitializerFunc_##identifier()

#endif // STATIC_INITIALIZE_H
