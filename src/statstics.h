class STATISTICS
{
public:
        int tgGoal[MAX_LOCATIONS][UNIT_TYPE_COUNT];
        struct boLog
        {
                int count;
                int order;
        } bolog[MAX_LENGTH],globalForcelog[MAX_GOALS];


        // TODO: make some significant variables...
        int run,rfit,afit,sfit;
        int counter;
        int time_graphics_counter, resources_graphics_counter;

        int old_time,old_pFitness,old_sFitness,old,old_t,old_sup,generation,calc,t,time_difference,resources_difference;
}

