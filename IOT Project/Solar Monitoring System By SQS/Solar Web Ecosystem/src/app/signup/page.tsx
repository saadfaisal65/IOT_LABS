"use client";

import * as React from "react";
import { useRouter } from "next/navigation";

import { createSupabaseBrowserClient } from "@/lib/supabase/client";
import { getPublicSiteUrl } from "@/lib/site-url";
import { Button } from "@/components/ui/button";
import { Card, CardContent, CardDescription, CardHeader, CardTitle } from "@/components/ui/card";
import { Input } from "@/components/ui/input";
import { Label } from "@/components/ui/label";
import { ThemeToggle } from "@/components/theme-toggle";
import { CreditFooter } from "@/components/credit-footer";

export default function SignupPage() {
  const router = useRouter();
  const [email, setEmail] = React.useState("");
  const [password, setPassword] = React.useState("");
  const [loading, setLoading] = React.useState(false);
  const [error, setError] = React.useState<string | null>(null);
  const [message, setMessage] = React.useState<string | null>(null);

  function mapSignupError(err: any): string {
    const msg = String(err?.message ?? "");
    // Supabase commonly returns variants of these for duplicate emails.
    if (/already\s*registered|already\s*in\s*use|user\s*already\s*exists/i.test(msg)) {
      return "An account with this email already exists. Please sign in.";
    }
    if (String(err?.status ?? "") === "422") {
      return "An account with this email already exists. Please sign in.";
    }
    return msg || "Signup failed";
  }

  async function onSubmit(e: React.FormEvent) {
    e.preventDefault();
    setError(null);
    setMessage(null);
    setLoading(true);
    try {
      const supabase = createSupabaseBrowserClient();
      const { data, error: signUpError } = await supabase.auth.signUp({
        email,
        password,
        options: {
          emailRedirectTo: `${getPublicSiteUrl()}/auth/callback`,
        },
      });
      if (signUpError) throw signUpError;

      // Supabase can return a user without an error when the email already exists.
      // In that case, it typically returns an empty identities array.
      const identitiesCount = data?.user?.identities?.length ?? 0;
      if (data?.user && identitiesCount === 0) {
        setError("An account with this email already exists. Please sign in.");
        return;
      }

      setMessage("Account created. Please check your email to confirm your address.");
    } catch (err: any) {
      setError(mapSignupError(err));
    } finally {
      setLoading(false);
    }
  }

  return (
    <div className="min-h-screen bg-gradient-to-b from-background via-background to-muted/30 flex flex-col p-4">
      <div className="flex-1 flex items-center justify-center">
        <div className="w-full max-w-md animate-in fade-in-0 slide-in-from-bottom-3 duration-500 motion-reduce:animate-none">
          <div className="flex justify-end pb-3">
            <ThemeToggle />
          </div>
          <Card>
            <CardHeader>
              <CardTitle>Create your account</CardTitle>
              <CardDescription>Use your email address to create a SolarSQS account</CardDescription>
            </CardHeader>
            <CardContent>
              <form onSubmit={onSubmit} className="space-y-4">
              <div className="space-y-2">
                <Label htmlFor="email">Email address</Label>
                <Input
                  id="email"
                  type="email"
                  autoComplete="email"
                  value={email}
                  onChange={(e) => setEmail(e.target.value)}
                  required
                />
              </div>
              <div className="space-y-2">
                <Label htmlFor="password">Password</Label>
                <Input
                  id="password"
                  type="password"
                  autoComplete="new-password"
                  value={password}
                  onChange={(e) => setPassword(e.target.value)}
                  required
                />
              </div>
              {error ? <p className="text-sm text-red-600">{error}</p> : null}
              {message ? <p className="text-sm text-green-700">{message}</p> : null}
              <Button type="submit" className="w-full" disabled={loading}>
                {loading ? "Creating..." : "Sign up"}
              </Button>
              <div className="text-sm text-muted-foreground">
                Already have an account?{" "}
                <a
                  className="underline underline-offset-4 transition-colors hover:text-foreground"
                  href="/login"
                >
                  Sign in
                </a>
              </div>
              </form>
            </CardContent>
          </Card>
        </div>
      </div>
      <CreditFooter className="pb-2" />
    </div>
  );
}
