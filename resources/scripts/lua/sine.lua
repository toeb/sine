
print("class",Class.UserDataStruct);
object = Class.UserDataStruct:new();
--print("object againg",aasd);
print(object:Action1());
print(object:Action2());
print(object:Value1());
print(object:Value2());
print(object:Value1(42));
print(object:Value2(43));
print(object:Value1());
print(object:Value2());


object = Nil;
print("collecting garbage")
collectgarbage();


print("Ende des scripts");
