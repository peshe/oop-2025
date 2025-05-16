class String {
  char *data{nullptr};

  void destroy();
  void assign(const char *value);

public:
  String() = default;
  String(const char *value);
  String(const String &other);
  String &operator=(const String &other);
  ~String();

  const char *getData() const { return data; }
};
