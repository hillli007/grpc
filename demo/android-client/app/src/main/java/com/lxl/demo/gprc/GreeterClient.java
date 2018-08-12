// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from greeter.djinni

package com.lxl.demo.gprc;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class GreeterClient {
    public abstract String HeartBeat(String platform, String name, String pwd);

    public abstract String LogOut(String platform, String name, String pwd);

    public abstract String SignIn(String platform, String name, String pwd);

    public abstract String SignUp(String name, String pwd);

    private static final class CppProxy extends GreeterClient
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            destroy();
            super.finalize();
        }

        @Override
        public String HeartBeat(String platform, String name, String pwd)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_HeartBeat(this.nativeRef, platform, name, pwd);
        }
        private native String native_HeartBeat(long _nativeRef, String platform, String name, String pwd);

        @Override
        public String LogOut(String platform, String name, String pwd)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_LogOut(this.nativeRef, platform, name, pwd);
        }
        private native String native_LogOut(long _nativeRef, String platform, String name, String pwd);

        @Override
        public String SignIn(String platform, String name, String pwd)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_SignIn(this.nativeRef, platform, name, pwd);
        }
        private native String native_SignIn(long _nativeRef, String platform, String name, String pwd);

        @Override
        public String SignUp(String name, String pwd)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_SignUp(this.nativeRef, name, pwd);
        }
        private native String native_SignUp(long _nativeRef, String name, String pwd);
    }
}
