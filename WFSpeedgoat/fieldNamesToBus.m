function [bus, busBytes] = fieldNamesToBus(fieldNames, name, desc)
    % Based on a struct of datanames + datatypes, constructs a simulink bus
    % type

    elements(numel(fieldNames(:,1))) = Simulink.BusElement;  % preallocate
    
    for i = 1:size(fieldNames, 1)
        elements(i)           = Simulink.BusElement;
        elements(i).Name      = fieldNames{i, 1};
        elements(i).DataType  = fieldNames{i, 2};
        elements(i).Dimensions = 1;
        elements(i).DimensionsMode = 'Fixed';
        elements(i).SampleTime = -1;
        elements(i).Complexity = 'real';
    end
    
    % --- Assemble the bus ---
    bus             = Simulink.Bus;
    bus.Description = sprintf('%s: %s', name, desc);
    bus.DataScope   = 'Auto';
    bus.Elements    = elements;
        
    busBytes = 0;
    for i = 1:size(fieldNames, 1)
        busBytes = busBytes + sizeof(bus.Elements(i).DataType);
    end
    
    fprintf('Bus ''%s'' defined: %d fields, %d bytes total\n', ...
            name, size(fieldNames, 1), busBytes);
end

