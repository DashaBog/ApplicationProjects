#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace Geometry {
const double kEps = 1e-9;

class Vector;

class IShape;
class Point;
class Segment;
class Ray;
class Line;
class Circle;

class Vector {
 public:
  Vector() = default;
  Vector(int abscissa, int ordinate) : abscissa_(abscissa), ordinate_(ordinate){};
  Vector(const Point& begin, const Point& end);

  int GetX() const { return abscissa_; }
  int GetY() const { return ordinate_; }

  double operator*(Vector value) const;
  double operator^(Vector value) const;
  Vector operator+(Vector value) const;
  Vector operator+=(Vector value);
  Vector operator-(Vector value) const;
  Vector operator-=(Vector value);
  Vector operator*(int value) const;
  Vector operator*=(int value);
  Vector operator-();

  double Length() const;

 private:
  int abscissa_;
  int ordinate_;
};

class IShape {
 public:
  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual IShape* Clone() const = 0;
  virtual std::string ToString() = 0;
  virtual ~IShape() = default;
};

class Point : public IShape {
 public:
  Point() = default;
  Point(int new_x, int new_y) : abscissa_(new_x), ordinate_(new_y){};

  int GetX() const { return abscissa_; }
  int GetY() const { return ordinate_; }
  int& SetX() { return abscissa_; }
  int& SetY() { return ordinate_; }

  Point& Move(const Vector& value) override;
  bool ContainsPoint(const Point& value) const override;
  bool CrossesSegment(const Segment& value) const override;
  Point* Clone() const override;
  std::string ToString() override;
  Vector operator-(const Point& value) const;

 private:
  int abscissa_;
  int ordinate_;
};

class Segment : public IShape {
 public:
  Segment() = default;
  Segment(const Point& first, const Point& second) : beginseg_(Point(first)), endseg_(Point(second)){};

  Point GetA() const { return beginseg_; }
  Point GetB() const { return endseg_; }

  Segment& Move(const Vector& value) override;
  bool ContainsPoint(const Point& value) const override;
  bool CrossesSegment(const Segment& value) const override;
  Segment* Clone() const override;
  std::string ToString() override;

 private:
  Point beginseg_;
  Point endseg_;
};

class Ray : public IShape {
 public:
  Point GetA() { return beginseg_; }
  Point GetVector() { return endseg_; }

  Ray() = default;
  Ray(int first, int second, int third, int fourth) : beginseg_(first, second), endseg_(third - first, fourth - second){};

  Ray& Move(const Vector& value) override;
  bool ContainsPoint(const Point& value) const override;
  bool CrossesSegment(const Segment& value) const override;
  Ray* Clone() const override;
  std::string ToString() override;
  bool LCrossesSegment(const Segment& value) const;

 private:
  Point beginseg_;
  Point endseg_;
};

class Line : public IShape {
 public:
  int x_1;
  int y_1;
  int x_2;
  int y_2;

  Line() = default;
  Line(int x1, int y1, int x2, int y2) : x_1(x1), y_1(y1), x_2(x2), y_2(y2){};
  Line(const Point& p1, const Point& p2)
      : x_1(p1.GetX()), y_1(p1.GetY()), x_2(p2.GetX()), y_2(p2.GetY()){};

  Line& Move(const Vector& v) override;
  bool ContainsPoint(const Point& p) const override;
  bool CrossesSegment(const Segment& s) const override;
  Line* Clone() const override;
  std::string ToString() override;
};

class Circle : public IShape {
 public:
  int x;
  int y;
  int r;

  Circle() = default;
  Circle(int new_x, int new_y, int new_r) : x(new_x), y(new_y), r(new_r){};
  Circle(const Point& p, int new_r) : x(p.GetX()), y(p.GetY()), r(new_r){};

  Circle& Move(const Vector& v) override;
  bool ContainsPoint(const Point& p) const override;
  bool CrossesSegment(const Segment& s) const override;
  Circle* Clone() const override;
  std::string ToString() override;
};

double Vector::operator*(Vector value) const {
  double scal = value.abscissa_ * abscissa_ + value.ordinate_ * ordinate_;
  return scal;
}

double Vector::operator^(Vector value) const {
  double vect = abscissa_ * value.ordinate_ - ordinate_ * value.abscissa_;
  return vect;
}

Vector Vector::operator+(Vector value) const { return Vector(abscissa_ + value.abscissa_, ordinate_ + value.ordinate_); }

Vector Vector::operator+=(Vector value) {
  abscissa_ += value.abscissa_;
  ordinate_ += value.ordinate_;
  return *this;
}

Vector Vector::operator-(Vector value) const { return Vector(abscissa_ - value.abscissa_, ordinate_ - value.ordinate_); }

Vector Vector::operator-=(Vector value) {
  abscissa_ -= value.abscissa_;
  ordinate_ -= value.ordinate_;
  return *this;
}

Vector Vector::operator*(int value) const { return Vector(value * abscissa_, value * ordinate_); }

Vector Vector::operator*=(int value) {
  abscissa_ *= value;
  ordinate_ *= value;
  return *this;
}

Vector Vector::operator-() {
  abscissa_ = -abscissa_;
  ordinate_ = -ordinate_;
  return Vector();
}

double Vector::Length() const { return sqrt(abscissa_ * abscissa_ + ordinate_ * ordinate_); }

Vector::Vector(const Point& begin, const Point& end) {
  abscissa_ = end.GetX() - begin.GetX();
  ordinate_ = end.GetY() - begin.GetY();
}

Point& Point::Move(const Vector& value) {
  abscissa_ += value.GetX();
  ordinate_ += value.GetY();
  return *this;
}

bool Point::ContainsPoint(const Point& value) const { return abscissa_ == value.abscissa_ && ordinate_ == value.ordinate_; }

bool Point::CrossesSegment(const Segment& value) const {
  double vect =
      (abscissa_ - value.GetA().abscissa_) * (value.GetB().ordinate_ - value.GetA().ordinate_) - (ordinate_ - value.GetA().ordinate_) * (value.GetB().abscissa_ - value.GetA().abscissa_);
  if (vect == 0) {
    if (std::min(value.GetA().ordinate_, value.GetB().ordinate_) <= ordinate_ && (std::max(value.GetA().ordinate_, value.GetB().ordinate_) >= ordinate_) &&
        std::min(value.GetA().abscissa_, value.GetB().abscissa_) <= abscissa_ && std::max(value.GetA().abscissa_, value.GetB().abscissa_) >= abscissa_) {
      return true;
    }
  }
  return false;
}

Point* Point::Clone() const { return new Point(*this); }

std::string Point::ToString() {
  std::string output = "Point(" + std::to_string(abscissa_) + ", " + std::to_string(ordinate_) + ")";
  return output;
}

Vector Point::operator-(const Point& value) const {
  return Vector(abscissa_ - value.abscissa_, ordinate_ - value.ordinate_);
}

Segment& Segment::Move(const Vector& value) {
  GetA().Move(value);
  GetB().Move(value);
  return *this;
}

int Det(int first, int second, int third, int fourth) { return first * fourth - second * third; }

bool Between(int first, int second, long double third) {
  return std::min(first, second) <= third && third <= std::max(first, second);
}

bool Intersect(int first, int second, int third, int fourth) {
  if (first > second) {
    std::swap(first, second);
  }
  if (third > fourth) {
    std::swap(third, fourth);
  }
  return std::max(first, third) <= std::min(second, fourth);
}

bool Segment::ContainsPoint(const Point& value) const {
  return value.CrossesSegment(*this);
}

bool Segment::CrossesSegment(const Segment& s) const {
  // 1 seg to line
  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  a1 = (GetB().GetY() - GetA().GetY());
  b1 = (GetA().GetX() - GetB().GetX());
  c1 = -a1 * GetA().GetX() - b1 * GetA().GetY();

  // 2 seg to line
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  a2 = (s.GetB().GetY() - s.GetA().GetY());
  b2 = (s.GetA().GetX() - s.GetB().GetX());
  c2 = -a2 * s.GetA().GetX() - b2 * s.GetA().GetY();

  double zn = Det(a1, b1, a2, b2);

  if (zn == 0) {
    return Det(a1, c1, a2, c2) == 0 && Det(b1, c1, b2, c2) == 0 &&
        Intersect(GetA().GetX(), GetB().GetX(), s.GetA().GetX(), s.GetB().GetX()) &&
        Intersect(GetA().GetY(), GetB().GetY(), s.GetA().GetY(), s.GetB().GetY());
  }

  double x = -Det(c1, b1, c2, b2) / zn;
  double y = -Det(a1, c1, a2, c2) / zn;

  return Between(GetA().GetX(), GetB().GetX(), x) && Between(GetA().GetY(), GetB().GetY(), y) &&
      Between(s.GetA().GetX(), s.GetB().GetX(), x) && Between(s.GetA().GetY(), s.GetB().GetY(), y);
}

Segment* Segment::Clone() const { return new Segment(*this); }

std::string Segment::ToString() {
  Point p1(GetA().GetX(), GetA().GetY());
  Point p2(GetB().GetX(), GetB().GetY());
  std::string s = "Segment(" + p1.ToString() + ", " + p2.ToString() + ")";
  return s;
}

Ray& Ray::Move(const Vector& value) {
  beginseg_.SetX() += value.GetX();
  beginseg_.SetY() += value.GetY();
  return *this;
}

bool Ray::ContainsPoint(const Point& value) const {
  return (value.GetX() - beginseg_.GetX()) * endseg_.GetY() == endseg_.GetX() * (value.GetY() - beginseg_.GetY()) && (value.GetX() - beginseg_.GetX()) * endseg_.GetX() >= 0 &&
      (value.GetY() - beginseg_.GetY()) * endseg_.GetY() >= 0;
}

bool Ray::CrossesSegment(const Segment& s) const {
  int a2 = 0;
  int b2 = 0;
  int c2 = 0;
  a2 = s.GetB().GetY() - s.GetA().GetY();
  b2 = s.GetA().GetX()-+ - s.GetB().GetX();
  c2 = -a2 * s.GetA().GetX() - b2 * s.GetA().GetY();

  int a1 = 0;
  int b1 = 0;
  int c1 = 0;
  a1 = beginseg_.GetY() + endseg_.GetY() - beginseg_.GetY();
  b1 = beginseg_.GetX() - endseg_.GetX() - beginseg_.GetX();
  c1 = -a1 * beginseg_.GetX() - b1 * beginseg_.GetY();

  double zn = Det(a1, b1, a2, b2);

  if (zn == 0) {
    return Det(a1, c1, a2, c2) == 0 && Det(b1, c1, b2, c2) == 0;
  }

  int ix = static_cast<int>(-Det(c1, b1, c2, b2) / zn);
  int iy = static_cast<int>(-Det(a1, c1, a2, c2) / zn);

  return Between(s.GetA().GetX(), s.GetB().GetX(), ix) && Between(s.GetA().GetY(), s.GetB().GetY(), iy) &&
      this->ContainsPoint(Point(ix, iy));
}

Ray* Ray::Clone() const { return new Ray(*this); }

std::string Ray::ToString() {
  Point p(beginseg_);
  Vector v(endseg_.GetX(), endseg_.GetY());
  return "Ray(" + p.ToString() + ", " + "Vector(" + std::to_string(v.GetX()) + ", " +
      std::to_string(v.GetY()) + ")" + ")";
}

Line& Line::Move(const Vector& v) {
  x_1 += v.GetX();
  y_1 += v.GetY();
  x_2 += v.GetX();
  y_2 += v.GetY();
  return *this;
}

bool Line::ContainsPoint(const Point& p) const {
  double vect = (p.GetX() - x_1) * (y_2 - y_1) - (p.GetY() - y_1) * (x_2 - x_1);
  return vect == 0;
}

bool Line::CrossesSegment(const Segment& s) const {
  double a1 = 0;
  double b1 = 0;
  double c1 = 0;
  a1 = y_2 - y_1;
  b1 = x_1 - x_2;
  c1 = x_2 * y_1 - x_1 * y_2;

  double a2 = 0;
  double b2 = 0;
  double c2 = 0;
  a2 = s.GetB().GetY() - s.GetA().GetY();
  b2 = s.GetA().GetX() - s.GetB().GetX();
  c2 = s.GetB().GetX() * s.GetA().GetY() - s.GetA().GetX() * s.GetB().GetY();

  if (a1 * b2 - a2 * b1 == 0) {
    return a1 * c2 - a2 * c1 == 0 && c1 * b2 - c2 * b1 == 0;
  }

  double x = (b1 * c2 - b2 * c1) / (a1 * b2 - b1 * a2);
  double y = (c1 * a2 - c2 * a1) / (a1 * b2 - b1 * a2);
  Point p(static_cast<int>(x), static_cast<int>(y));

  return s.ContainsPoint(p);
}

Line* Line::Clone() const { return new Line(*this); }

std::string Line::ToString() {
  std::string a1;
  std::string b1;
  std::string c1;
  a1 = std::to_string(y_2 - y_1);
  b1 = std::to_string(x_1 - x_2);
  c1 = std::to_string(x_2 * y_1 - x_1 * y_2);

  std::string s = "Line(" + a1 + ", " + b1 + ", " + c1 + ")";
  return s;
}

bool Ray::LCrossesSegment(const Segment& s) const {
  return ((s.GetA().GetY() < beginseg_.GetY() && s.GetB().GetY() > beginseg_.GetY() - kEps) ||
      (s.GetB().GetY() < beginseg_.GetY() && s.GetA().GetY() > beginseg_.GetY() - kEps)) &&
      (beginseg_.GetY() * (s.GetA().GetX() - s.GetB().GetX()) + s.GetA().GetY() * s.GetB().GetX() - s.GetA().GetX() * s.GetB().GetY()) /
          (s.GetA().GetY() - s.GetB().GetY()) < beginseg_.GetX();
}

Circle& Circle::Move(const Vector& v) {
  x += v.GetX();
  y += v.GetY();
  return *this;
}

bool Circle::ContainsPoint(const Point& p) const {
  return (p.GetX() - x) * (p.GetX() - x) + (p.GetY() - y) * (p.GetY() - y) <= r * r;
}

bool PointInC(const Circle& c, const Point& p) {
  return (p.GetX() - c.x) * (p.GetX() - c.x) + (p.GetY() - c.y) * (p.GetY() - c.y) < c.r * c.r;
}

bool Circle::CrossesSegment(const Segment& s) const {
  Point p1(s.GetA().GetX(), s.GetA().GetY());
  Point p2(s.GetB().GetX(), s.GetB().GetY());
  Point p(x, y);

  Vector v0(p1, p2);
  Vector v1(p1, p);
  Vector v2(p, p2);

  double dist1 = v1.Length();
  double dist2 = v2.Length();

  double dist = 0;

  if (v0 * v1 <= 0 || v0 * v2 <= 0) {
    dist = std::min(dist1, dist2);
  } else {
    dist = ((p1.GetY() - p2.GetY()) * p.GetX() + (p1.GetX() - p2.GetX()) * p.GetY() +
        (p1.GetX() * p2.GetY() - p2.GetX() * p1.GetY())) /
        v0.Length();
  }

  if (PointInC(*this, p1) && PointInC(*this, p2)) {
    return false;
  }

  return dist <= r;
}

Circle* Circle::Clone() const { return new Circle(*this); }

std::string Circle::ToString() {
  Point p(static_cast<int>(x), static_cast<int>(y));
  std::string s = "Circle(" + p.ToString() + ", " + std::to_string(r) + ")";
  return s;
}
}  // namespace Geometry

template <class SmartPtrT>
void Delete(const SmartPtrT& unused) {}

template <class T>
void Delete(T* ptr) {
  delete ptr;
}