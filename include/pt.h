template <typename T>
class Pt {
public:
  Pt () : _x (0), _y (0) {}
  Pt (T x, T y) : _x (x), _y (y) {}
  
  T x () const {return _x;}
  T y () const {return _y;}

  T& x () {return _x;}
  T& y () {return _y;}
private:
  T _x;
  T _y;
};

