function [taskInfo, numtask, isDeploymentDiagram]=slrealtime_task_info()
   taskInfo(1).samplePeriod = 0.01;
   taskInfo(1).sampleOffset = 0.0;
   taskInfo(1).taskPrio = 12;
   taskInfo(1).taskName = 'BaseRate';
   taskInfo(1).entryPoints = {};
   taskInfo(2).samplePeriod = 0.1;
   taskInfo(2).sampleOffset = 0.0;
   taskInfo(2).taskPrio = 11;
   taskInfo(2).taskName = ['SubRate' '1'];        
   taskInfo(2).entryPoints = {};
   taskInfo(3).samplePeriod = 0.25;
   taskInfo(3).sampleOffset = 0.0;
   taskInfo(3).taskPrio = 10;
   taskInfo(3).taskName = ['SubRate' '2'];        
   taskInfo(3).entryPoints = {};
   taskInfo(4).samplePeriod = 0.5;
   taskInfo(4).sampleOffset = 0.0;
   taskInfo(4).taskPrio = 9;
   taskInfo(4).taskName = ['SubRate' '3'];        
   taskInfo(4).entryPoints = {};
   numtask = 4;
   for i = 1:numtask
      if ( 0 == isnumeric(taskInfo(i).samplePeriod) )
         taskInfo(i).samplePeriod = evalin('base', taskInfo(i).samplePeriod);
      end
      if ( isempty(taskInfo(i).taskName) )
         taskInfo(i).taskName = ['AutoGen' i ];
      end
   end
   isDeploymentDiagram = 0;
end 
