#ifndef DEFAULTDEFS_H
#define DEFAULTDEFS_H


enum tabletypes{
TTYPE_ABSTRACT = 0x10001,
TTYPE_TABLE = 0x10003,
TTYPE_EXPRESSION = 0x10005
};

enum linktypes{
TTYPE_LINK = 0x10008,
TTYPE_CUSTOM_LINK = 0x10018,
TTYPE_FOREIGN_LINK = 0x10028
};


enum coltypes {
CTYPE_NORMAL,
CTYPE_HEADER,
CTYPE_HEADER_SELECTED,
CTYPE_CUSTOM_SELECTED =4,
CTYPE_OUTPUTFIELD = 8,
CTYPE_WHERE_FIELD = 16
};

/*

template <typename T>
class QForeachTypedContainer {
public:
    inline QForeachTypedContainer(const T& t) : c(t), brk(0), i(c.begin()), e(c.end()) { }
    const T c;
    int brk;
    typename T::const_iterator i, e;
};


   foreach (QGraphicsItem *  item, items()) {
       if((item->type() & TTYPE_TABLE) == TTYPE_TABLE )
        {
           crtableitem *  table = static_cast< crtableitem *>(item);
           if(table->tablestring.startsWith(alias))aliascount++;

       }



#define Q_FOREACHTYPED(variable, container,cont_type)                                \
for (QForeachTypedContainer<__typeof__(container)> _container_(container); \
     !_container_.brk && _container_.i != _container_.e;              \
     __extension__  ({ ++_container_.brk; ++_container_.i; }))                       \
    for (variable = *_container_.i;; __extension__ ({--_container_.brk; break;}))  \



#define foreachtyped Q_FOREACHTYPED

*/


#endif // DEFAULTDEFS_H
