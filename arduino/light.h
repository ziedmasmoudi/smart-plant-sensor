class LIGHT {
    int ldrPin{0};
    
    public:
        bool create(int ldrPin);
        int getIntensity();
};