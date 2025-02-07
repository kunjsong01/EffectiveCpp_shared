namespace WidgetStuff {

class WidgetImpl { // class for Widget data;
  public:          // details are unimportant
    //...
  private:
    int a, b, c;           // lots of data —
    std::vector<double> v; // expensive to copy!
    //...
};

class Widget { // class using the pimpl idiom
  public:
    Widget(WidgetImpl * ptr): 
      pImpl(ptr) { }

    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs) { 
      // ...
      *pImpl = *(rhs.pImpl);

      return *this;
    }

    ~Widget() {
      delete pImpl;
    }

    void swap(Widget& other) {
      using std::swap;
      swap(pImpl, other.pImpl);
    }
    // ...
  private:
    WidgetImpl *pImpl; // ptr to WidgetImpl object
}; 

// a nont member function in WidgetStuff namespace
void swap(Widget& a, Widget& b) {
  a.swap(b);
}

} // END OF WidgetStuff namespace

// code will be called like this: 
WidgetImpl* xData = new WidgetImpl();
WidgetImpl* yData = new WidgetImpl();

Widget wX(xData);
Widget wY(xData);

swap(wX, wY) // Would compiler call WidgetStuff::swap ???