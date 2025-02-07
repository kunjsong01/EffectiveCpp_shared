namespace WidgetStuff {

template<typename T>
class WidgetImpl { 
  public:          
    //...
  private:
    int a, b, c;         
    std::vector<T> v;  
    //...
};

template<typename T>
class Widget { // class using the pimpl idiom
  public:
    Widget(WidgetImpl<T> * ptr): 
      pImpl(ptr) { }

    Widget(const Widget<T>& rhs);
    Widget<T>& operator=(const Widget<T>& rhs) { 
      //...
      *pImpl = *(rhs.pImpl);

      return *this;
    }

    ~Widget() {
      delete pImpl;
    }

    // Is this the swap member function Scott refers to? 
    void swap(Widget<T>& other) {
      using std::swap;
      swap(pImpl, other.pImpl);
    }

    // ...
  private:
    WidgetImpl<T> *pImpl; // ptr to WidgetImpl<T> object
}; 

template<typename T>
void swap(Widget<T>& a, Widget<T>& b) {
  a.swap(b);
}

} // END OF WidgetStuff namespace

// Scott advice: "T-specific specialization of std::swap over the general template"
// 我的理解是： 这是个“双保险”。如果有人写std::swap(wX, wY)，编译器也会用下面这个specialization 这样理解对吗？
namespace std {
  template<>
  void swap<Widget<double> >(Widget<double>& a, Widget<double>& b)
  { a.swap(b); }
} // END OF function template specialization in std namespace

// code will be called like this: 
WidgetImpl<double>* xData = new WidgetImpl<double>();
WidgetImpl<double>* yData = new WidgetImpl<double>();

Widget<double> wX(xData);
Widget<double> wY(yData);

swap(wX, wY) // Would compiler call WidgetStuff::swap ???

// if people call std::swap(wX, wY), 我们已经有了双保险 （53行） --- 这样理解对吗？
// std::swap(wX, wY) // should work as intended