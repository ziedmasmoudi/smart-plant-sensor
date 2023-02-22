class MOISTURE {
  int powerPin {0};
  int signalPin {0};
  public:
      bool create(int powerPIN, int signalPIN);

      int getValue();
};
