package cz.cvut.fit.vwm.mtree;

import java.util.List;

/**
 *
 * @author george
 */
public class DistanceFunctionImpl implements DistanceFunction {
    public static Double computeEuclidean(List<Double> data1, List<Double> data2){
        double result = 0;
        
        for(int i = 0; i < data1.size(); i++){
            result += (data1.get(i) - data2.get(i))*(data1.get(i) - data2.get(i));
        }
        return Math.sqrt(result);
        
    }

    @Override
    public Double compute(List<Double> data1, List<Double> data2) {
        return computeEuclidean(data1, data2);
    }
}
