function S = sizeof(X)
switch X
    case {'uint64', 'int64', 'double'}
        m = 8;
    case {'uint32', 'int32', 'single'}
        m = 4;
    case {'uint16', 'int16', 'char'}
        m = 2;
    case {'uint8', 'int8', 'logical'}
        m = 1;
    otherwise
        error('Jan:sizeof:Type', 'Type not handles: %s', class(X));
end
% S = m * numel(X);
S = m;
end
